#include "app_validation.h"
#include "ota_config.h"

uint8_t IsApplicationValid(void)
{
    uint32_t appStackPointer;
    uint32_t resetHandler;

    appStackPointer = *(volatile uint32_t *)APPLICATION_START_ADDRESS;
    resetHandler    = *(volatile uint32_t *)(APPLICATION_START_ADDRESS + 4U);

    /* Validate Stack Pointer */
    if((appStackPointer < RAM_START_ADDRESS) ||
       (appStackPointer >= RAM_END_ADDRESS))
    {
        return 0;
    }

    /* Validate Reset Handler */
    if((resetHandler < APPLICATION_START_ADDRESS) ||
       (resetHandler >= FLASH_END_ADDRESS))
    {
        return 0;
    }

    return 1;
}
