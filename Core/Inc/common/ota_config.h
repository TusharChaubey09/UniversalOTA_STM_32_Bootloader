#ifndef OTA_CONFIG_H
#define OTA_CONFIG_H

/* Bootloader Configuration */

#define BOOTLOADER_START_ADDRESS    0x08000000U
#define BOOTLOADER_SIZE             (16 * 1024U)

/* Application Configuration */

#define APPLICATION_START_ADDRESS   0x08004000U

/* Flash Configuration */

#define INTERNAL_FLASH_SIZE         (128 * 1024U)

/* OTA Configuration */

#define OTA_PENDING_FLAG   0xA5A5A5A5U


#define OTA_FLAG_ADDRESS            0x0801F000U

#define OTA_METADATA_ADDRESS    0x00000000U

#define OTA_FIRMWARE_ADDRESS    0x00001000U

#define OTA_METADATA_MAGIC    0x4F544131U

#define FIRMWARE_VERSION_ADDRESS    0x0801F800U

#endif
