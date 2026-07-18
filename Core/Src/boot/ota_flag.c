#include "ota_flag.h"
#include "ota_config.h"
#include "flash_utils.h"

uint8_t OTA_IsUpdatePending(void)
{
    uint64_t value;

    value = Flash_ReadDoubleWord(OTA_FLAG_ADDRESS);

    return (value == OTA_PENDING_FLAG);
}

void OTA_SetUpdatePending(void)
{
    Flash_WriteDoubleWord(OTA_FLAG_ADDRESS,
                          OTA_PENDING_FLAG);
}

void OTA_ClearUpdatePending(void)
{
    Flash_WriteDoubleWord(OTA_FLAG_ADDRESS,
                          0);
}
