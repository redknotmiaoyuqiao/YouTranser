#ifndef YOUTRANSLOADING_HPP
#define YOUTRANSLOADING_HPP

#include "YouCommon/LoginWindow.h"
#include "YouCommon/LoadingWindow.h"
#include "YouCommon/MediaEyeApplication.h"

#include "YouTransAppConfig.hpp"

namespace Eyer
{
    class YouTransLoading : public LoadingWindow
    {
    public:
        YouTransLoading(const YouTransAppConfig & app, QWidget *parent = nullptr);
        virtual ~YouTransLoading();

        virtual int GotoLogin() override;
        virtual int GotoMain() override;
    };
}


#endif // YOUTRANSLOADING_HPP
