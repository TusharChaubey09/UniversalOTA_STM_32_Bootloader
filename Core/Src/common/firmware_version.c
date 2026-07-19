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

    char versionBuffer[FIRMWARE_VERSION_LENGTH];

    memset(
            versionBuffer,
            0xFF,
            sizeof(versionBuffer));

    strncpy(
            versionBuffer,
            version,
            FIRMWARE_VERSION_LENGTH);

    Flash_ErasePage(63);

    for(uint32_t i = 0; i < FIRMWARE_VERSION_LENGTH; i += 8)
    {
        uint64_t data = 0xFFFFFFFFFFFFFFFFULL;

        uint32_t copySize = 8;

        if((FIRMWARE_VERSION_LENGTH - i) < 8)
        {
            copySize = FIRMWARE_VERSION_LENGTH - i;
        }

        memcpy(
                &data,
                &versionBuffer[i],
                copySize);

        Flash_WriteApplication(
                address,
                data);

        address += 8;
    }
}
