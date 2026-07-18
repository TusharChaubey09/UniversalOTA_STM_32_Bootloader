#ifndef OTA_METADATA_H
#define OTA_METADATA_H

#include <stdint.h>

#define OTA_FIRMWARE_VERSION_SIZE      32
#define OTA_AES_IV_SIZE                16
#define OTA_HMAC_SIZE                  32
#define OTA_RESERVED_EXTENSION_SIZE    28

typedef struct
{
    uint32_t magicNumber;

    uint16_t metadataVersion;

    uint16_t headerSize;

    char firmwareVersion[OTA_FIRMWARE_VERSION_SIZE];

    uint32_t firmwareSize;

    uint32_t mcuFamilyID;

    uint8_t forceOverride;

    uint8_t encryptionType;

    uint8_t hashType;

    uint8_t reservedFlags;

    uint8_t iv[OTA_AES_IV_SIZE];

    uint8_t hmac[OTA_HMAC_SIZE];

    uint8_t reservedExtension[OTA_RESERVED_EXTENSION_SIZE];

} OTA_Metadata_t;

typedef enum
{
    MCU_STM32G0 = 1

} MCU_Family_t;

#endif
