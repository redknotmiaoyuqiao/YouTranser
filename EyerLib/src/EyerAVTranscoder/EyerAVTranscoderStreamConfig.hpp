#ifndef EYERLIB_EYERAVTRANSCODERSTREAMCONFIG_HPP
#define EYERLIB_EYERAVTRANSCODERSTREAMCONFIG_HPP

#include "EyerAV/EyerAVHeader.hpp"

namespace Eyer
{
    class EyerAVTranscoderStreamConfig
    {
    public:
        EyerAVTranscoderStreamConfig();
        ~EyerAVTranscoderStreamConfig();
        EyerAVTranscoderStreamConfig(const EyerAVTranscoderStreamConfig & streamConfig);
        EyerAVTranscoderStreamConfig & operator = (const EyerAVTranscoderStreamConfig & streamConfig);

    private:
        EyerAVStreamType streamType = EyerAVStreamType::MEDIA_TYPE_VIDEO;
        EyerAVCodecID codecId = EyerAVCodecID::CODEC_ID_H264;
    };
}

#endif //EYERLIB_EYERAVTRANSCODERSTREAMCONFIG_HPP
