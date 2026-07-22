#include "firmware_version.h"
#include "ota_config.h"
#include "flash_programmer.h"

#include <string.h>

void FirmwareVersion_GetCurrent(char *version)
{
    memcpy(
            version,
            (const void *)FIRMWARE_VERSION_ADDRESS,
            FIRMWARE_VERSION_LENGTH);
}

void FirmwareVersion_SetCurrent(const char *version)
{
    uint32_t address = FIRMWARE_VERSION_ADDRESS;

    Flash_ErasePage(63);

    for(uint32_t i = 0; i < FIRMWARE_VERSION_LENGTH; i += 8)
    {
        uint64_t data = 0xFFFFFFFFFFFFFFFFULL;

        memcpy(
                &data,
                &version[i],
                8);

        Flash_WriteApplication(
                address,
                data);

        address += 8;
    }
}
