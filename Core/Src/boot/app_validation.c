#include "app_validation.h"
#include "ota_config.h"

uint8_t IsApplicationValid(void)
{
    uint32_t appStackPointer;

    appStackPointer = *(volatile uint32_t*)APPLICATION_START_ADDRESS;

    if((appStackPointer & 0x2FFE0000U) == 0x20000000U)
    {
        return 1;
    }

    return 0;
}
