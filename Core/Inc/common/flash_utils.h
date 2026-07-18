#ifndef FLASH_UTILS_H
#define FLASH_UTILS_H

#include <stdint.h>

void Flash_WriteDoubleWord(uint32_t address,
                           uint64_t data);

uint64_t Flash_ReadDoubleWord(uint32_t address);

void Flash_ErasePage(uint32_t pageAddress);

#endif
