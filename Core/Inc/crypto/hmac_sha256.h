#ifndef HMAC_SHA256_H
#define HMAC_SHA256_H

#include <stdint.h>
#include "sha256.h"

#define HMAC_SHA256_SIZE          32
#define SHA256_BLOCK_SIZE_BYTES   64

typedef struct
{
    SHA256_CTX innerCtx;
    SHA256_CTX outerCtx;
} HMAC_SHA256_CTX;

/*--------------------------------------------------------------------
 * Streaming HMAC API
 *-------------------------------------------------------------------*/

void HMAC_SHA256_Init(
        HMAC_SHA256_CTX *ctx,
        const uint8_t *key,
        uint32_t keyLength);

void HMAC_SHA256_Update(
        HMAC_SHA256_CTX *ctx,
        const uint8_t *data,
        uint32_t length);

void HMAC_SHA256_Final(
        HMAC_SHA256_CTX *ctx,
        uint8_t *hmac);

/*--------------------------------------------------------------------
 * Convenience API
 *-------------------------------------------------------------------*/

void HMAC_SHA256_Generate(
        const uint8_t *key,
        uint32_t keyLength,
        const uint8_t *data,
        uint32_t length,
        uint8_t *hmac);

uint8_t HMAC_SHA256_Verify(
        const uint8_t *key,
        uint32_t keyLength,
        const uint8_t *data,
        uint32_t length,
        const uint8_t *expectedHMAC);

#endif
