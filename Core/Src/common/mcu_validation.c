#include "mcu_validation.h"

uint8_t ValidateMCU(
        const OTA_Metadata_t *metadata)
{
    if(metadata->mcuFamilyID != MCU_STM32G0)
    {
        return 0;
    }

    return 1;
}
