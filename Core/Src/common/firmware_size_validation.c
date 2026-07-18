#include "firmware_size_validation.h"

#define MAX_APPLICATION_SIZE    (112U * 1024U)

uint8_t ValidateFirmwareSize(
        const OTA_Metadata_t *metadata)
{
    if(metadata->firmwareSize == 0)
    {
        return 0;
    }

    if(metadata->firmwareSize > MAX_APPLICATION_SIZE)
    {
        return 0;
    }

    return 1;
}
