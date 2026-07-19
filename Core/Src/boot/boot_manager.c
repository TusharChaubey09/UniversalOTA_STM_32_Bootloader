#include "main.h"
#include "boot_manager.h"
#include "jump_to_app.h"
#include "app_validation.h"
#include "install_firmware.h"
#include "ota_flag.h"
#include "metadata_reader.h"
#include "metadata_validation.h"
#include "version_validation.h"
#include "crypto_manager.h"
#include "firmware_verify.h"
#include "firmware_version.h"
#include "w25q128.h"
#include "mcu_validation.h"
#include "firmware_size_validation.h"
void BootManager_Init(void)
{
	W25Q128_Init();
}

void BootManager_Run(void)
{
	OTA_Metadata_t metadata;
	if(OTA_IsUpdatePending())
	{
	    OTA_ReadMetadata(&metadata);

	    if(ValidateMetadata(&metadata) &&
	       ValidateMCU(&metadata) &&
	       ValidateFirmwareSize(&metadata))
	    {
	        if(metadata.forceOverride ||
	           ValidateFirmwareVersion(metadata.firmwareVersion))
	        {
	        	if(InstallFirmware())
	        	{
	        	    FirmwareVersion_SetCurrent(
	        	            metadata.firmwareVersion);

	        	    OTA_ClearUpdatePending();
	        	}
	        }
	    }
	}

    if(IsApplicationValid())
    {
        JumpToApplication();
    }

    while(1)
    {
        HAL_GPIO_TogglePin(Boot_LED_GPIO_Port,
                           Boot_LED_Pin);

        HAL_Delay(500);
    }
}
