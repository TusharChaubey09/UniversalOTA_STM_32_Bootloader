#include "flash_programmer.h"
#include "ota_config.h"
#include "stm32g0xx_hal.h"

void Flash_EraseApplication(void)
{
    FLASH_EraseInitTypeDef eraseInit;
    uint32_t pageError = 0;

    HAL_FLASH_Unlock();

    eraseInit.TypeErase = FLASH_TYPEERASE_PAGES;

    eraseInit.Banks = FLASH_BANK_1;

    eraseInit.Page = 8;

    eraseInit.NbPages = 56;

    HAL_FLASHEx_Erase(&eraseInit,
                      &pageError);

    HAL_FLASH_Lock();
}
void Flash_ErasePage(uint32_t pageNumber)
{
    FLASH_EraseInitTypeDef eraseInit;
    uint32_t pageError = 0;

    HAL_FLASH_Unlock();

    eraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
    eraseInit.Banks = FLASH_BANK_1;
    eraseInit.Page = pageNumber;
    eraseInit.NbPages = 1;

    HAL_FLASHEx_Erase(&eraseInit, &pageError);

    HAL_FLASH_Lock();
}
void Flash_WriteApplication(uint32_t address,
                            uint64_t data)
{
    HAL_FLASH_Unlock();

    HAL_FLASH_Program(
            FLASH_TYPEPROGRAM_DOUBLEWORD,
            address,
            data);

    HAL_FLASH_Lock();
}
