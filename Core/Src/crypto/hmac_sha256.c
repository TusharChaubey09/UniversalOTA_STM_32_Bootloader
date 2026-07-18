#include "hmac_sha256.h"
#include "crypto_manager.h"

#include <string.h>
static uint8_t ipad[SHA256_BLOCK_SIZE_BYTES];
static uint8_t opad[SHA256_BLOCK_SIZE_BYTES];

void HMAC_SHA256_Init(
        HMAC_SHA256_CTX *ctx,
        const uint8_t *key,
        uint32_t keyLength)
{
    uint8_t keyBlock[SHA256_BLOCK_SIZE_BYTES];
    uint32_t i;

    memset(keyBlock, 0, sizeof(keyBlock));

    /*
     * RFC2104:
     * If the key is longer than the SHA256 block size,
     * hash it first.
     */
    if(keyLength > SHA256_BLOCK_SIZE_BYTES)
    {
        SHA256_CTX shaCtx;

        sha256_init(&shaCtx);
        sha256_update(&shaCtx, key, keyLength);
        sha256_final(&shaCtx, keyBlock);
    }
    else
    {
        memcpy(keyBlock, key, keyLength);
    }

    for(i = 0; i < SHA256_BLOCK_SIZE_BYTES; i++)
    {
        ipad[i] = keyBlock[i] ^ 0x36;
        opad[i] = keyBlock[i] ^ 0x5C;
    }

    sha256_init(&ctx->innerCtx);
    sha256_update(
            &ctx->innerCtx,
            ipad,
            SHA256_BLOCK_SIZE_BYTES);

    sha256_init(&ctx->outerCtx);
    sha256_update(
            &ctx->outerCtx,
            opad,
            SHA256_BLOCK_SIZE_BYTES);
}
void HMAC_SHA256_Update(
        HMAC_SHA256_CTX *ctx,
        const uint8_t *data,
        uint32_t length)
{
    sha256_update(
            &ctx->innerCtx,
            data,
            length);
}
void HMAC_SHA256_Final(
        HMAC_SHA256_CTX *ctx,
        uint8_t *hmac)
{
    uint8_t innerHash[HMAC_SHA256_SIZE];

    /*
     * Finish:
     *
     * SHA256(ipad || message)
     */
    sha256_final(
            &ctx->innerCtx,
            innerHash);

    /*
     * Continue:
     *
     * SHA256(opad || innerHash)
     */
    sha256_update(
            &ctx->outerCtx,
            innerHash,
            HMAC_SHA256_SIZE);

    sha256_final(
            &ctx->outerCtx,
            hmac);
}
void HMAC_SHA256_Generate(
        const uint8_t *key,
        uint32_t keyLength,
        const uint8_t *data,
        uint32_t length,
        uint8_t *hmac)
{
    HMAC_SHA256_CTX ctx;

    HMAC_SHA256_Init(
            &ctx,
            key,
            keyLength);

    HMAC_SHA256_Update(
            &ctx,
            data,
            length);

    HMAC_SHA256_Final(
            &ctx,
            hmac);
}
uint8_t HMAC_SHA256_Verify(
        const uint8_t *key,
        uint32_t keyLength,
        const uint8_t *data,
        uint32_t length,
        const uint8_t *expectedHMAC)
{
    uint8_t calculatedHMAC[HMAC_SHA256_SIZE];

    HMAC_SHA256_Generate(
            key,
            keyLength,
            data,
            length,
            calculatedHMAC);

    if(memcmp(
            calculatedHMAC,
            expectedHMAC,
            HMAC_SHA256_SIZE) == 0)
    {
        return 1;
    }

    return 0;
}
