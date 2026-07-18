#include "jump_to_app.h"
#include "ota_config.h"
#include <stdint.h>
#include "stm32g0xx.h"
typedef void (*pFunction)(void);

void JumpToApplication(void)
{
    uint32_t appStackPointer;
    uint32_t appResetHandler;

    pFunction JumpToApp;

    appStackPointer = *(volatile uint32_t*)APPLICATION_START_ADDRESS;
    appResetHandler = *(volatile uint32_t*)(APPLICATION_START_ADDRESS + 4U);

    __disable_irq();

    __set_MSP(appStackPointer);

    JumpToApp = (pFunction)appResetHandler;

    JumpToApp();
}
