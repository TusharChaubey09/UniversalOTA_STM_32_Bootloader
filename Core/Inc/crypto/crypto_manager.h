#ifndef CRYPTO_MANAGER_H
#define CRYPTO_MANAGER_H

#include <stdint.h>

extern const uint8_t OTA_AES_Key[32];

extern const uint8_t OTA_Default_IV[16];

extern const uint8_t OTA_HMAC_Key[32];

uint8_t Crypto_VerifyHMAC(
        const uint8_t *data,
        uint32_t length,
        const uint8_t *expectedHMAC);

uint8_t Crypto_DecryptFirmware(
        uint8_t *buffer,
        uint32_t length,
        const uint8_t *iv);

#endif
