#include "hmac_sha256.h"
#include "crypto_manager.h"

static const uint8_t TestData[] = "Hello OTA";

uint8_t HMACTest_Output[32];

void HMACTest_Run(void)
{
    HMAC_SHA256_Generate(
            OTA_HMAC_Key,
            sizeof(OTA_HMAC_Key),
            TestData,
            sizeof(TestData) - 1,
            HMACTest_Output);
}
