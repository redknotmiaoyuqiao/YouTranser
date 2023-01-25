#ifndef YOUTRANSLOGIN_HPP
#define YOUTRANSLOGIN_HPP

#include "YouCommon/LoginWindow.h"
#include "YouCommon/LoadingWindow.h"
#include "YouCommon/MediaEyeApplication.h"

#include "YouTransAppConfig.hpp"

namespace Eyer
{
    class YouTransLogin : public LoginWindow
    {
    public:
        YouTransLogin(const YouTransAppConfig & app, QWidget *parent = nullptr);

        virtual int GotoMain() override;
    };
}

#endif // YOUTRANSLOGIN_HPP
