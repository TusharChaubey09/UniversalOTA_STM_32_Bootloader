#ifndef W25Q128_H
#define W25Q128_H

#include <stdint.h>

void W25Q128_Init(void);

uint32_t W25Q128_ReadID(void);

void W25Q128_WriteEnable(void);

uint8_t W25Q128_ReadStatus(void);

void W25Q128_WaitBusy(void);

void W25Q128_ReadData(uint32_t address,
                      uint8_t *buffer,
                      uint32_t length);
void W25Q128_PageProgram(uint32_t address,
                         const uint8_t *buffer,
                         uint16_t length);

void W25Q128_EraseSector(uint32_t address);

#endif
