#ifndef YOUPICKERLOADING_HPP
#define YOUPICKERLOADING_HPP

#include "YouCommon/LoginWindow.h"
#include "YouCommon/LoadingWindow.h"
#include "YouCommon/MediaEyeApplication.h"

#include "YouPickerAppConfig.hpp"

namespace Eyer
{
    class YouPickerLoading : public LoadingWindow
    {
    public:
        YouPickerLoading(const YouPickerAppConfig & app, QWidget *parent = nullptr);
        virtual ~YouPickerLoading();

        virtual int GotoLogin() override;
        virtual int GotoMain() override;
    };
}


#endif // YOUPICKERLOADING_HPP
