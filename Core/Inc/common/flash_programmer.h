#ifndef FLASH_PROGRAMMER_H
#define FLASH_PROGRAMMER_H

#include <stdint.h>

void Flash_EraseApplication(void);

void Flash_WriteDoubleWord(uint32_t address,
                           uint64_t data);
uint8_t Flash_WriteApplication(uint32_t address,
                               uint64_t data);

void Flash_ErasePage(uint32_t pageNumber);

#endif
