#include "YouTransLogin.hpp"

#include "YouTransMainWindow.hpp"

namespace Eyer
{
    YouTransLogin::YouTransLogin(const YouTransAppConfig & app, QWidget *parent)
        : LoginWindow(app, parent)
    {

    }

    int YouTransLogin::GotoMain()
    {
        YouTransMainWindow * main = new YouTransMainWindow();
        main->show();
        return 0;
    }
}
