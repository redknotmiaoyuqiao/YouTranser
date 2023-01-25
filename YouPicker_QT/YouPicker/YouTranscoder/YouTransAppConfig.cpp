#include "YouTransAppConfig.hpp"


namespace Eyer
{
    YouTransAppConfig::YouTransAppConfig()
    {
        char versionStr[128];
        sprintf(versionStr, "%s %s", __DATE__,__TIME__);

        appName                     = "YouTranser";
        appId                       = "YouTranser";
        companyName                 = "www.zzsin.com";
        version                     = "Release: " + QString(versionStr);
        logoPath                    = ":/img/logo/logo_256.png";

        KEY_TOKEN                   = "YOU_TRANS_TOKEN";
        KEY_EMAIL                   = "YOU_TRANS_EMAIL";
        KEY_TOKEN_UPDATE_TIME       = "YOU_TRANS_TOKEN_TIME";

        loginUrl                    = "https://www.zzsin.com/eye/user/login/login";
        loginCheckUrl               = "https://www.zzsin.com/eye/user/token/check";
    }

    QString YouTransAppConfig::Get_TRANS_MAIN_BUTTON_SET_INPUT_PATH()
    {
        return "输入文件";
    }

    QString YouTransAppConfig::Get_TRANS_MAIN_BUTTON_SET_OUTPUT_PATH()
    {
        return "输出文件";
    }

    QString YouTransAppConfig::Get_TRANS_MAIN_BUTTON_START_TRANS_CODE()
    {
        return "开始转码";
    }

    QString YouTransAppConfig::Get_TRANS_MAIN_BUTTON_START_SETTING_CONFIG()
    {
        return "设置参数";
    }



    QString YouTransAppConfig::Get_TRANS_CONFIG_WINDOWS_TITLE()
    {
        return "设置转码参数";
    }

    QString YouTransAppConfig::Get_TRANS_CONFIG_AVFILEFMT()
    {
        return "输出格式";
    }

    QString YouTransAppConfig::Get_TRANS_CONFIG_SET_VIDEO()
    {
        return "视频参数";
    }

    QString YouTransAppConfig::Get_TRANS_CONFIG_SET_AUDIO()
    {
        return "音频参数";
    }

    QString YouTransAppConfig::Get_TRANS_CONFIG_BUTTON_OK()
    {
        return "确定";
    }

    QString YouTransAppConfig::Get_TRANS_CONFIG_BUTTON_CANCEL()
    {
        return "取消";
    }

    QString YouTransAppConfig::Get_TRANS_CONFIG_VIDEOCODEC_LABEL()
    {
        return "视频编码：";
    }

    QString YouTransAppConfig::Get_TRANS_CONFIG_PIXELFMT_LABEL()
    {
        return "像素格式：";
    }

    QString YouTransAppConfig::Get_TRANS_CONFIG_CRF_LABEL()
    {
        return "CRF：";
    }

    QString YouTransAppConfig::Get_TRANS_CONFIG_AUDIOCODEC_LABEL()
    {
        return "音频编码：";
    }

    QString YouTransAppConfig::Get_TRANS_CONFIG_CHANNEL_LAYOUT_LABEL()
    {
        return "声道布局：";
    }

    QString YouTransAppConfig::Get_TRANS_CONFIG_SAMPLE_RATE_LABEL()
    {
        return "采样率：";
    }

    QString YouTransAppConfig::Get_TRANS_CONFIG_SET_FILENAME_LABEL()
    {
        return "输出文件名配置：";
    }

    QString YouTransAppConfig::Get_TRAND_CONFIG_FILENAME_LABEL()
    {
        QString label = "";
        label += "原始文件名：${origin_file_name}\n";
        label += "输出视频编码：${output_video_codec}\n";
        label += "输出像素格式：${video_pixelfmt}\n";
        label += "输出音频编码：${output_audio_codec}\n";
        return label;
    }
}
