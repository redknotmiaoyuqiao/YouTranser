#include "YouPickerAppConfig.hpp"

#include <stdio.h>

namespace Eyer
{
    YouPickerAppConfig::YouPickerAppConfig()
    {
        char versionStr[128];
        sprintf(versionStr, "%s %s", __DATE__,__TIME__);

        appName                     = "YouPicker";
        appId                       = "YouPicker";
        companyName                 = "www.zzsin.com";
        version                     = "Release: " + QString(versionStr);
        logoPath                    = ":/img/logo/CodecEye_H_264.png";

        KEY_TOKEN                   = "YOU_PICKER_TOKEN";
        KEY_EMAIL                   = "YOU_PICKER_EMAIL";
        KEY_TOKEN_UPDATE_TIME       = "YOU_PICKER_TOKEN_TIME";

        loginUrl                    = "https://www.zzsin.com/eye/user/login/login";
        loginCheckUrl               = "https://www.zzsin.com/eye/user/token/check";
    }
}
