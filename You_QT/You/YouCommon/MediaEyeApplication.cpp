#include "MediaEyeApplication.h"

MediaEyeApplication::MediaEyeApplication()
{
    appName                     = "Codec Eye";
    appId                       = "CodecEye";
    companyName                 = "ZigZagSin";
    version                     = "beta 0.0.6";
    logoPath                    = ":/img/logo/CodecEye_H_264.png";

    KEY_TOKEN                   = "FRAME_EYE_TOKEN";
    KEY_EMAIL                   = "FRAME_EYE_EMAIL";
    KEY_TOKEN_UPDATE_TIME       = "FRAME_EYE_TOKEN_TIME";

    loginUrl                    = "https://www.zzsin.com/eye/user/login/login";
    loginCheckUrl               = "https://www.zzsin.com/eye/user/token/check";
}

MediaEyeApplication::~MediaEyeApplication()
{

}

MediaEyeApplication::MediaEyeApplication(const MediaEyeApplication & app)
{
    *this = app;
}

const MediaEyeApplication & MediaEyeApplication::operator = (const MediaEyeApplication & app)
{
    appName = app.appName;
    appId = app.appId;

    version = app.version;

    logoPath = app.logoPath;

    companyName = app.companyName;

    KEY_TOKEN = app.KEY_TOKEN;
    KEY_EMAIL = app.KEY_EMAIL;
    KEY_TOKEN_UPDATE_TIME = app.KEY_TOKEN_UPDATE_TIME;

    loginCheckUrl = app.loginCheckUrl;
    loginUrl = app.loginUrl;

    return *this;
}

const QString & MediaEyeApplication::GetAppName()
{
    return appName;
}

const QString & MediaEyeApplication::GetAppId()
{
    return appId;
}

const QString & MediaEyeApplication::GetVersion()
{
    return version;
}

const QString & MediaEyeApplication::GetCompanyName()
{
    return companyName;
}

const QString & MediaEyeApplication::GetLoginURL()
{
    return loginUrl;
}

const QString & MediaEyeApplication::GetLoginCheckURL()
{
    return loginCheckUrl;
}

const QString & MediaEyeApplication::GetKEY_EMAIL()
{
    return KEY_EMAIL;
}

const QString & MediaEyeApplication::GetKEY_TOKEN()
{
    return KEY_TOKEN;
}

const QString & MediaEyeApplication::GetKEY_TOKEN_UPDATE_TIME()
{
    return KEY_TOKEN_UPDATE_TIME;
}

const QString & MediaEyeApplication::GetLogoPath()
{
    return logoPath;
}
