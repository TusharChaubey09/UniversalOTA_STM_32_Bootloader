#include "metadata_validation.h"
#include "ota_config.h"
#include <string.h>

uint8_t ValidateMetadata(const OTA_Metadata_t *metadata)
{
    if(metadata->magicNumber != OTA_METADATA_MAGIC)
    {
        return 0;
    }

    if(metadata->metadataVersion != 1)
    {
        return 0;
    }

    if(metadata->headerSize != sizeof(OTA_Metadata_t))
    {
        return 0;
    }

    if(metadata->firmwareSize == 0)
    {
        return 0;
    }

    if(metadata->firmwareSize > (112 * 1024))
    {
        return 0;
    }

    if(metadata->firmwareVersion[0] == '\0')
    {
        return 0;
    }

    if(metadata->mcuFamilyID != MCU_STM32G0)
    {
        return 0;
    }

    return 1;
}
