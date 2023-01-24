#ifndef EYERLIB_EYERAVENCODER_HPP
#define EYERLIB_EYERAVENCODER_HPP

#include "EyerAVEncoderParam.hpp"

#include "EyerAVFrame.hpp"
#include "EyerAVPacket.hpp"
#include "EyerAVADTS.hpp"
#include "EyerAVMediaType.hpp"

namespace Eyer
{
    class EyerAVEncoderPrivate;

    class EyerAVEncoder {
    public:
        EyerAVEncoder();
        ~EyerAVEncoder();

        int Init(const EyerAVEncoderParam & param);

        int SendFrame(EyerAVFrame & frame);
        int SendFrameNull();
        int RecvPacket(EyerAVPacket & packet);

        int GetFrameSize();

        int GetTimebase(EyerAVRational & timebase);
        EyerAVRational GetTimebase();

        EyerAVMediaType GetMediaType();
        EyerAVChannelLayout GetChannelLayout();
        EyerAVSampleFormat GetSampleFormat();
        int GetSampleRate();

        EyerAVADTS GetADTS(int packetSize);

        EyerAVMediaType GetCodecType();

    private:
        EyerAVEncoder(const EyerAVEncoder & encoder) = delete;
        EyerAVEncoder & operator = (const EyerAVEncoder & encoder) = delete;

    public:
        EyerAVEncoderPrivate * piml = nullptr;
    };
}

#endif //EYERLIB_EYERAVENCODER_HPP
