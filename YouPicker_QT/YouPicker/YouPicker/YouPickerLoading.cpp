#include "YouPickerLoading.hpp"

#include "YouPickerLogin.hpp"
#include "YPSessionListWindow.hpp"

namespace Eyer
{
    YouPickerLoading::YouPickerLoading(const YouPickerAppConfig & app, QWidget * parent)
        : LoadingWindow(app, parent)
    {

    }

    YouPickerLoading::~YouPickerLoading()
    {

    }

    int YouPickerLoading::GotoLogin()
    {
        qDebug() << "GotoLogin" << Qt::endl;
        YouPickerAppConfig app;
        YouPickerLogin * login = new YouPickerLogin(app, this);
        login->show();
        return 0;
    }

    int YouPickerLoading::GotoMain()
    {
        qDebug() << "GotoMain" << Qt::endl;
        YouPickerAppConfig app;
        YPSessionListWindow * sessionList = new YPSessionListWindow(this);
        sessionList->show();
        return 0;
    }
}

