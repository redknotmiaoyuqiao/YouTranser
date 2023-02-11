#ifndef YOUPICKERLOGIN_HPP
#define YOUPICKERLOGIN_HPP

#include "YouCommon/LoginWindow.h"
#include "YouCommon/LoadingWindow.h"
#include "YouCommon/MediaEyeApplication.h"

#include "YouPickerAppConfig.hpp"

namespace Eyer
{
    class YouPickerLogin : public LoginWindow
    {
    public:
        YouPickerLogin(const YouPickerAppConfig & app, QWidget *parent = nullptr);

        virtual int GotoMain() override;
    };
}


#endif // YOUPICKERLOGIN_HPP
