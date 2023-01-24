#include "EyerLog.hpp"

namespace Eyer
{
    EyerString EyerVersion::GetEyerLibVersion()
    {
        char versionStr[256];
        sprintf(versionStr, "zzsin.com EyerLib version: %s %s", __DATE__,__TIME__);
        return versionStr;
    }
}