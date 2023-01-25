#ifndef YOUTRANSAPPCONFIG_HPP
#define YOUTRANSAPPCONFIG_HPP

#include "YouCommon/MediaEyeApplication.h"

namespace Eyer
{
    class YouTransAppConfig : public MediaEyeApplication
    {
    public:
        YouTransAppConfig();

        QString Get_TRANS_MAIN_BUTTON_SET_INPUT_PATH();
        QString Get_TRANS_MAIN_BUTTON_SET_OUTPUT_PATH();
        QString Get_TRANS_MAIN_BUTTON_START_TRANS_CODE();
        QString Get_TRANS_MAIN_BUTTON_START_SETTING_CONFIG();

        QString Get_TRANS_CONFIG_WINDOWS_TITLE();
        QString Get_TRANS_CONFIG_AVFILEFMT();
        QString Get_TRANS_CONFIG_SET_VIDEO();
        QString Get_TRANS_CONFIG_SET_AUDIO();
        QString Get_TRANS_CONFIG_BUTTON_OK();
        QString Get_TRANS_CONFIG_BUTTON_CANCEL();

        QString Get_TRANS_CONFIG_VIDEOCODEC_LABEL();
        QString Get_TRANS_CONFIG_PIXELFMT_LABEL();
        QString Get_TRANS_CONFIG_CRF_LABEL();
        QString Get_TRANS_CONFIG_AUDIOCODEC_LABEL();
        QString Get_TRANS_CONFIG_CHANNEL_LAYOUT_LABEL();
        QString Get_TRANS_CONFIG_SAMPLE_RATE_LABEL();

        QString Get_TRANS_CONFIG_SET_FILENAME_LABEL();
        QString Get_TRAND_CONFIG_FILENAME_LABEL();
    };
}

#endif // YOUTRANSAPPCONFIG_HPP
