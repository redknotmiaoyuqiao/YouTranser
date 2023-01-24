#include "EyerAVTranscoderParams.hpp"

namespace Eyer
{
    EyerAVTranscoderParams::EyerAVTranscoderParams()
    {

    }

    EyerAVTranscoderParams::~EyerAVTranscoderParams()
    {

    }

    EyerAVTranscoderParams::EyerAVTranscoderParams(const EyerAVTranscoderParams & _params)
    {
        *this = _params;
    }

    EyerAVTranscoderParams & EyerAVTranscoderParams::operator = (const EyerAVTranscoderParams & _params)
    {
        outputFileFmt = _params.outputFileFmt;

        outputVideoCodec = _params.outputVideoCodec;
        outputVideoPixelFormat = _params.outputVideoPixelFormat;

        outputAudioCodec = _params.outputAudioCodec;
        outputChannelLayout = _params.outputChannelLayout;

        width = _params.width;
        height = _params.height;

        sampleRate = _params.sampleRate;

        crf = _params.crf;

        decodeThreadNum = _params.decodeThreadNum;
        encodeThreadNum = _params.encodeThreadNum;

        return *this;
    }

    const EyerAVFileFmt EyerAVTranscoderParams::GetOutputFileFmt() const
    {
        return outputFileFmt;
    }

    const EyerAVCodecID EyerAVTranscoderParams::GetVideoCodecId() const
    {
        return outputVideoCodec;
    }

    const EyerAVPixelFormat EyerAVTranscoderParams::GetVideoPixelFormat() const
    {
        return outputVideoPixelFormat;
    }

    int EyerAVTranscoderParams::SetWidthHeight(int w, int h)
    {
        width   = w;
        height  = h;
        return 0;
    }

    const int EyerAVTranscoderParams::GetWidth() const
    {
        return width;
    }

    const int EyerAVTranscoderParams::GetHeight() const
    {
        return height;
    }

    int EyerAVTranscoderParams::SetCRF(int _crf)
    {
        crf = _crf;
        return 0;
    }

    const int EyerAVTranscoderParams::GetCRF() const
    {
        return crf;
    }




    const EyerAVCodecID EyerAVTranscoderParams::GetAudioCodecId() const
    {
        return outputAudioCodec;
    }

    const EyerAVChannelLayout EyerAVTranscoderParams::GetAudioChannelLayout() const
    {
        return outputChannelLayout;
    }


    int EyerAVTranscoderParams::SetOutputFileFmt(const EyerAVFileFmt & _fileFmt)
    {
        outputFileFmt = _fileFmt;
        return 0;
    }

    int EyerAVTranscoderParams::SetVideoCodecId(const EyerAVCodecID & _codecId)
    {
        outputVideoCodec = _codecId;
        return 0;
    }

    int EyerAVTranscoderParams::SetVideoPixelFormat(const EyerAVPixelFormat & _pixFmt)
    {
        outputVideoPixelFormat = _pixFmt;
        return 0;
    }

    int EyerAVTranscoderParams::SetAudioCodecId(const EyerAVCodecID & _codecId)
    {
        outputAudioCodec = _codecId;
        return 0;
    }

    int EyerAVTranscoderParams::SetChannelLayout(const EyerAVChannelLayout & _channelLayout)
    {
        outputChannelLayout = _channelLayout;
        return 0;
    }

    int EyerAVTranscoderParams::SetSampleRate(int _sampleRate)
    {
        sampleRate = _sampleRate;
        return 0;
    }

    const int EyerAVTranscoderParams::GetSampleRate() const
    {
        return sampleRate;
    }

    const int EyerAVTranscoderParams::GetDecodeThreadNum() const
    {
        return decodeThreadNum;
    }

    const int EyerAVTranscoderParams::GetEncodeThreadNum() const
    {
        return encodeThreadNum;
    }

    int EyerAVTranscoderParams::SetDecodeThreadNum(int num)
    {
        decodeThreadNum = num;
        return 0;
    }

    int EyerAVTranscoderParams::SetEncodeThreadNum(int num)
    {
        encodeThreadNum = num;
        return 0;
    }

    EyerString EyerAVTranscoderParams::ToString()
    {
        EyerString str = "";
        str += EyerString("outputFileFmt: ") + outputFileFmt.GetDesc() + "\n";

        str += EyerString("outputVideoCodec: ") + outputVideoCodec.GetDescName() + "\n";
        str += EyerString("outputVideoPixelFormat: ") + outputVideoPixelFormat.GetDescName() + "\n";
        str += EyerString("width: ") + EyerString::Number(width) + "\n";
        str += EyerString("height: ") + EyerString::Number(height) + "\n";
        str += EyerString("crf: ") + EyerString::Number(crf) + "\n";

        str += EyerString("outputAudioCodec: ") + outputAudioCodec.GetDescName() + "\n";
        str += EyerString("outputChannelLayout: ") + outputChannelLayout.GetDescName() + "\n";
        str += EyerString("sampleRate: ") + EyerString::Number(sampleRate) + "\n";
        str += EyerString("decodeThreadNum: ") + EyerString::Number(decodeThreadNum) + "\n";
        str += EyerString("encodeThreadNum: ") + EyerString::Number(encodeThreadNum) + "\n";

        return str;
    }
}