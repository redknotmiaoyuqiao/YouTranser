#ifndef MEDIAEYEAPPLICATION_H
#define MEDIAEYEAPPLICATION_H

#include <QString>

class MediaEyeApplication
{
public:
    MediaEyeApplication();
    ~MediaEyeApplication();

    MediaEyeApplication(const MediaEyeApplication & app);

    const MediaEyeApplication & operator = (const MediaEyeApplication & app);

    const QString & GetAppName();
    const QString & GetAppId();
    const QString & GetVersion();

    const QString & GetCompanyName();

    const QString & GetKEY_EMAIL();
    const QString & GetKEY_TOKEN();
    const QString & GetKEY_TOKEN_UPDATE_TIME();

    const QString & GetLoginURL();
    const QString & GetLoginCheckURL();

    const QString & GetLogoPath();

protected:
    QString appName;
    QString appId;
    QString version;

    QString companyName;
    QString logoPath;

    QString loginUrl;
    QString loginCheckUrl;

    QString KEY_EMAIL;
    QString KEY_TOKEN;
    QString KEY_TOKEN_UPDATE_TIME;
};

#endif // MEDIAEYEAPPLICATION_H
