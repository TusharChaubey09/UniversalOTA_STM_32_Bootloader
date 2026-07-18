#include "flash_utils.h"
#include "stm32g0xx_hal.h"

uint64_t Flash_ReadDoubleWord(uint32_t address)
{
    return *((uint64_t*)address);
}

void Flash_WriteDoubleWord(uint32_t address,
                           uint64_t data)
{
    HAL_FLASH_Unlock();

    HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,
                      address,
                      data);

    HAL_FLASH_Lock();
}
