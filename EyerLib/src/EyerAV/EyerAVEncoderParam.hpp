#ifndef EYERLIB_EYERAVENCODERPARAM_HPP
#define EYERLIB_EYERAVENCODERPARAM_HPP

#include "EyerAVRational.hpp"
#include "EyerAVStream.hpp"
#include "EyerAVChannelLayout.hpp"
#include "EyerAVSampleFormat.hpp"
#include "EyerAVPixelFormat.hpp"
#include "EyerAVCodecID.hpp"

namespace Eyer
{
    class EyerAVEncoderParam {
    public:
        EyerAVEncoderParam();
        ~EyerAVEncoderParam();

        EyerAVEncoderParam(const EyerAVEncoderParam & params);
        EyerAVEncoderParam & operator = (const EyerAVEncoderParam & params);

        int InitProres(int _width, int _height, const EyerAVRational & _timebase, const EyerAVPixelFormat & _pixelFormat);

        int InitH264(int width, int height, int fps, const EyerAVPixelFormat & pixelFormat, int crf = 23);
        int InitH264(int width, int height, const EyerAVRational & _timebase, const EyerAVPixelFormat & pixelFormat, int crf = 23);

        int InitH265(int width, int height, int fps, const EyerAVPixelFormat & pixelFormat, int crf = 23);
        int InitH265(int width, int height, const EyerAVRational & _timebase, const EyerAVPixelFormat & pixelFormat, int crf = 23);


        int InitVP8(int width, int height, int fps, const EyerAVPixelFormat & pixelFormat);
        int InitVP8(int width, int height, const EyerAVRational & _timebase, const EyerAVPixelFormat & pixelFormat);

        int InitVP9(int width, int height, int fps, const EyerAVPixelFormat & pixelFormat);
        int InitVP9(int width, int height, const EyerAVRational & _timebase, const EyerAVPixelFormat & pixelFormat);

        int InitVideo(EyerAVCodecID codecId, int width, int height, int fps, const EyerAVPixelFormat & pixelFormat);
        int InitVideo(EyerAVCodecID codecId, int width, int height, const EyerAVRational & _timebase, const EyerAVPixelFormat & pixelFormat);

        int InitAAC(EyerAVChannelLayout _channelLayout, EyerAVSampleFormat _sampleFormat, int _sample_rate);
        int InitFDKAAC(EyerAVChannelLayout _channelLayout, EyerAVSampleFormat _sampleFormat, int _sample_rate);
        int InitLibOpus(EyerAVChannelLayout _channelLayout, EyerAVSampleFormat _sampleFormat, int _sample_rate);
        int InitMP3(EyerAVChannelLayout _channelLayout, EyerAVSampleFormat _sampleFormat, int _sample_rate);
        int InitFLAC(EyerAVChannelLayout _channelLayout, EyerAVSampleFormat _sampleFormat, int _sample_rate);
        int InitPCM_S16LE(EyerAVChannelLayout _channelLayout, EyerAVSampleFormat _sampleFormat, int _sample_rate);
        int InitPCM_S32LE(EyerAVChannelLayout _channelLayout, EyerAVSampleFormat _sampleFormat, int _sample_rate);

        int InitAudio(EyerAVCodecID codecId, EyerAVChannelLayout _channelLayout, EyerAVSampleFormat _sampleFormat, int _sample_rate);

        int InitJPEG(int width, int height);
        int InitPNG(int width, int height, const EyerAVPixelFormat & _pixelFormat);

        int InitSRT();

        int InitFromStream(const EyerAVStream & straem);
        int SetTimebase(const EyerAVRational & timebase);
        int SetWH(int width, int height);

    public:
        EyerAVCodecID codecId = EyerAVCodecID::CODEC_ID_UNKNOW;
        int width = 0;
        int height = 0;

        int crf = 18;
        int threadnum = 4;

        int sample_rate = 44100;
        EyerAVChannelLayout channelLayout;
        EyerAVSampleFormat sampleFormat;
        EyerAVPixelFormat pixelFormat;
        EyerAVRational timebase;
    };
}

#endif //EYERLIB_EYERAVENCODERPARAM_HPP
