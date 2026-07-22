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
#include "hmac_sha256.h"

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
    HMAC_SHA256_CTX hmacCtx;

    uint8_t calculatedHMAC[HMAC_SHA256_SIZE];



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
    /*----------------------------------------------------------
     * Streaming HMAC Verification
     *---------------------------------------------------------*/

    HMAC_SHA256_Init(
            &hmacCtx,
            OTA_HMAC_Key,
            sizeof(OTA_HMAC_Key));

    /* Hash metadata with HMAC field cleared */
    HMAC_SHA256_Update(
            &hmacCtx,
            (uint8_t *)&hmacMetadata,
            sizeof(OTA_Metadata_t));

    Flash_EraseApplication();

    bytesRemaining = metadata.firmwareSize;

    flashAddress = APPLICATION_START_ADDRESS;

    externalFlashAddress = OTA_FIRMWARE_ADDRESS;
    /* Initialize AES-CBC streaming context once */
    Crypto_AESInit(metadata.iv);

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
        /* Update HMAC using encrypted firmware */
        HMAC_SHA256_Update(
                &hmacCtx,
                firmwareBuffer,
                chunkSize);
        Crypto_AESDecryptChunk(
                firmwareBuffer,
                chunkSize);

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

            if(!Flash_WriteApplication(
                    flashAddress + i,
                    data))
            {
                return 0;
            }
        }

        bytesRemaining -= chunkSize;

        flashAddress += chunkSize;

        externalFlashAddress += chunkSize;
    }
    /* Finish HMAC calculation */
    HMAC_SHA256_Final(
            &hmacCtx,
            calculatedHMAC);

    /* Compare with metadata HMAC */
    if(memcmp(
            calculatedHMAC,
            metadata.hmac,
            HMAC_SHA256_SIZE) != 0)
    {
        /* Authentication failed */
        return 0;
    }
    if(!VerifyInstalledFirmware())
    {
        return 0;
    }

    /* Installation successful */
    OTA_ClearUpdatePending();

    /* Optional: update stored firmware version */
    // FirmwareVersion_SetCurrent(metadata.firmwareVersion);

    return 1;
}
