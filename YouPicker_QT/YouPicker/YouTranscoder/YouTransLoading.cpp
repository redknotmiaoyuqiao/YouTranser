#include "YouTransLoading.hpp"

#include "YouTransLogin.hpp"
#include "YouTransMainWindow.hpp"

namespace Eyer
{
    YouTransLoading::YouTransLoading(const YouTransAppConfig & app, QWidget *parent)
        : LoadingWindow(app, parent)
    {

    }

    YouTransLoading::~YouTransLoading()
    {

    }

    int YouTransLoading::GotoLogin()
    {
        qDebug() << "GotoLogin" << Qt::endl;
        Eyer::YouTransAppConfig app;
        YouTransLogin * login = new YouTransLogin(app);
        login->show();
        return 0;
    }

    int YouTransLoading::GotoMain()
    {
        qDebug() << "GotoMain" << Qt::endl;
        Eyer::YouTransAppConfig app;
        YouTransMainWindow * main = new YouTransMainWindow();
        main->show();
        return 0;
    }
}
