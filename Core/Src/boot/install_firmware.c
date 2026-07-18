#include "install_firmware.h"

#include "metadata_reader.h"

#include "flash_programmer.h"

#include "w25q128.h"

#include "ota_config.h"

#include <string.h>

#include "firmware_verify.h"

#include "ota_flag.h"

#include "metadata_validation.h"

#include "crypto_manager.h"

#include "mcu_validation.h"

#include "firmware_size_validation.h"

uint8_t InstallFirmware(void)

{
    OTA_Metadata_t metadata;

    OTA_Metadata_t hmacMetadata;

    uint8_t firmwareBuffer[256];

    uint32_t bytesRemaining;

    uint32_t flashAddress;

    uint32_t externalFlashAddress;

    OTA_ReadMetadata(&metadata);
    memcpy(
            &hmacMetadata,
            &metadata,
            sizeof(OTA_Metadata_t));

    memset(
            hmacMetadata.hmac,
            0,
            sizeof(hmacMetadata.hmac));



    if(!ValidateMetadata(&metadata))
    {
        return 0;
    }
    if(!ValidateMCU(&metadata))
    {
        return 0;
    }
    if(!ValidateFirmwareSize(&metadata))
    {
        return 0;
    }
    /*
     * TODO:
     * Verify HMAC over:
     * 1. Metadata header (with HMAC field zeroed)
     * 2. Encrypted firmware stored in W25Q128
     */

    Flash_EraseApplication();

    bytesRemaining = metadata.firmwareSize;

    flashAddress = APPLICATION_START_ADDRESS;

    externalFlashAddress = OTA_FIRMWARE_ADDRESS;

    while(bytesRemaining > 0)
    {
        uint32_t chunkSize;

        if(bytesRemaining >= 256)
        {
            chunkSize = 256;
        }
        else
        {
            chunkSize = bytesRemaining;
        }

        W25Q128_ReadData(
                externalFlashAddress,
                firmwareBuffer,
                chunkSize);
        Crypto_DecryptFirmware(
                firmwareBuffer,
                chunkSize,
                metadata.iv);

        for(uint32_t i = 0; i < chunkSize; i += 8)
        {
            uint64_t data = 0xFFFFFFFFFFFFFFFFULL;

            uint32_t copySize;

            if((chunkSize - i) >= 8)
            {
                copySize = 8;
            }
            else
            {
                copySize = chunkSize - i;
            }

            memcpy(&data,
                   &firmwareBuffer[i],
                   copySize);

            Flash_WriteApplication(
                    flashAddress + i,
                    data);
        }

        bytesRemaining -= chunkSize;

        flashAddress += chunkSize;

        externalFlashAddress += chunkSize;
    }

    if(VerifyInstalledFirmware())
    {
         return 0;
    }
    return 1;
}
