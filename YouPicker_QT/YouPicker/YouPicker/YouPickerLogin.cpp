#include "YouPickerLogin.hpp"

namespace Eyer
{
    YouPickerLogin::YouPickerLogin(const YouPickerAppConfig & app, QWidget *parent)
        : LoginWindow(app, parent)
    {

    }

    int YouPickerLogin::GotoMain()
    {
        return 0;
    }
}
