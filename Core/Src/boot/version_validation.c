#include "version_validation.h"
#include "firmware_version.h"
#include <string.h>
#include "ota_metadata.h"

uint8_t ValidateFirmwareVersion(
        const char *newVersion)
{
	char currentVersion[OTA_FIRMWARE_VERSION_SIZE];

    FirmwareVersion_GetCurrent(currentVersion);

    /*
     * Empty flash means first installation.
     */
    if(currentVersion[0] == (char)0xFF)
    {
        return 1;
    }

    /*
     * Version format:
     * YYYYMMDD_Vx.x
     *
     * Lexicographical comparison works correctly.
     */
    if(strcmp(newVersion, currentVersion) > 0)
    {
        return 1;
    }

    return 0;
}
