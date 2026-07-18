#include "firmware_verify.h"
#include "app_validation.h"

uint8_t VerifyInstalledFirmware(void)
{
    if(IsApplicationValid())
    {
        return 1;
    }

    return 0;
}
