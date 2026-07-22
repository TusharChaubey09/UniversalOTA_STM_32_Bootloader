#ifndef CRYPTO_MANAGER_H
#define CRYPTO_MANAGER_H

#include <stdint.h>
#include "aes.h"

extern const uint8_t OTA_AES_Key[32];
extern const uint8_t OTA_Default_IV[16];
extern const uint8_t OTA_HMAC_Key[32];

/* AES Streaming API */
void Crypto_AESInit(const uint8_t *iv);

void Crypto_AESDecryptChunk(uint8_t *buffer,
                            uint32_t length);

uint8_t Crypto_VerifyHMAC(
        const uint8_t *data,
        uint32_t length,
        const uint8_t *expectedHMAC);

#endif
