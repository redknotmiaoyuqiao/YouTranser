#ifndef EYERLIB_EYERAVTRANSCODERPARAMS_HPP
#define EYERLIB_EYERAVTRANSCODERPARAMS_HPP

#include "EyerAV/EyerAVHeader.hpp"

namespace Eyer
{
    class EyerAVTranscoderParams
    {
    public:
        EyerAVTranscoderParams();
        ~EyerAVTranscoderParams();

        EyerAVTranscoderParams(const EyerAVTranscoderParams & _params);
        EyerAVTranscoderParams & operator = (const EyerAVTranscoderParams & _params);

        const EyerAVFileFmt GetOutputFileFmt() const;

        const EyerAVCodecID GetVideoCodecId() const;
        const EyerAVPixelFormat GetVideoPixelFormat() const;

        const EyerAVCodecID GetAudioCodecId() const;
        const EyerAVChannelLayout GetAudioChannelLayout() const;

        int SetOutputFileFmt(const EyerAVFileFmt & fileFmt);

        int SetVideoCodecId(const EyerAVCodecID & _codecId);
        int SetVideoPixelFormat(const EyerAVPixelFormat & _pixFmt);
        int SetWidthHeight(int w, int h);
        const int GetWidth() const;
        const int GetHeight() const;

        int SetCRF(int _crf);
        const int GetCRF() const;

        int SetAudioCodecId(const EyerAVCodecID & _codecId);
        int SetChannelLayout(const EyerAVChannelLayout & _channelLayout);

        int SetSampleRate(int _sampleRate);

        const int GetSampleRate() const;

        const int GetDecodeThreadNum() const;
        const int GetEncodeThreadNum() const;

        int SetDecodeThreadNum(int num);
        int SetEncodeThreadNum(int num);

        EyerString ToString();

    private:
        EyerAVFileFmt outputFileFmt = EyerAVFileFmt::MOV;

        EyerAVCodecID outputVideoCodec = EyerAVCodecID::CODEC_ID_H265;
        EyerAVPixelFormat outputVideoPixelFormat = EyerAVPixelFormat::EYER_KEEP_SAME;
        int width = -1;
        int height = -1;
        int crf = 18;

        EyerAVCodecID outputAudioCodec = EyerAVCodecID::CODEC_ID_AAC;
        EyerAVChannelLayout outputChannelLayout = EyerAVChannelLayout::EYER_KEEP_SAME;
        int sampleRate = -2;

        int decodeThreadNum = 2;
        int encodeThreadNum = 2;
    };
}

#endif //EYERLIB_EYERAVTRANSCODERPARAMS_HPP
