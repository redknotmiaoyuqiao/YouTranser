#include "EyerAVEncoderParam.hpp"

#include "EyerAVStream.hpp"
#include "EyerAVStreamPrivate.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    EyerAVEncoderParam::EyerAVEncoderParam()
    {

    }

    EyerAVEncoderParam::~EyerAVEncoderParam()
    {

    }

    EyerAVEncoderParam::EyerAVEncoderParam(const EyerAVEncoderParam & params)
    {
        *this = params;
    }

    EyerAVEncoderParam & EyerAVEncoderParam::operator = (const EyerAVEncoderParam & params)
    {
        codecId     = params.codecId;
        width       = params.width;
        height      = params.height;
        sample_rate = params.sample_rate;
        timebase    = params.timebase;
        pixelFormat = params.pixelFormat;
        threadnum   = params.threadnum;
        return *this;
    }

    int EyerAVEncoderParam::InitH264(int width, int height, int fps, const EyerAVPixelFormat & pixelFormat, int _crf)
    {
        Eyer::EyerAVRational videoTimebase;
        videoTimebase.num = 1;
        videoTimebase.den = fps;

        return InitH264(width, height, videoTimebase, pixelFormat, _crf);
    }

    int EyerAVEncoderParam::InitH264(int _width, int _height, const EyerAVRational & _timebase, const EyerAVPixelFormat & _pixelFormat, int _crf)
    {
        codecId         = EyerAVCodecID::CODEC_ID_H264;
        width           = _width;
        height          = _height;
        timebase        = _timebase;
        pixelFormat     = _pixelFormat;
        crf             = _crf;
        return 0;
    }

    int EyerAVEncoderParam::InitH265(int width, int height, int fps, const EyerAVPixelFormat & _pixelFormat, int _crf)
    {
        Eyer::EyerAVRational videoTimebase;
        videoTimebase.num = 1;
        videoTimebase.den = fps;

        return InitH265(width, height, videoTimebase, _pixelFormat, _crf);
    }

    int EyerAVEncoderParam::InitH265(int _width, int _height, const EyerAVRational & _timebase, const EyerAVPixelFormat & _pixelFormat, int _crf)
    {
        codecId         = EyerAVCodecID::CODEC_ID_H265;
        width           = _width;
        height          = _height;
        timebase        = _timebase;
        pixelFormat     = _pixelFormat;
        crf             = _crf;
        return 0;
    }


    int EyerAVEncoderParam::InitVP8(int width, int height, int fps, const EyerAVPixelFormat & _pixelFormat)
    {
        Eyer::EyerAVRational videoTimebase;
        videoTimebase.num = 1;
        videoTimebase.den = fps;

        return InitVP8(width, height, videoTimebase, _pixelFormat);
    }

    int EyerAVEncoderParam::InitVP8(int _width, int _height, const EyerAVRational & _timebase, const EyerAVPixelFormat & _pixelFormat)
    {
        codecId         = EyerAVCodecID::CODEC_ID_VP8;
        width           = _width;
        height          = _height;
        timebase        = _timebase;
        pixelFormat     = _pixelFormat;
        return 0;
    }

    int EyerAVEncoderParam::InitVP9(int width, int height, int fps, const EyerAVPixelFormat & _pixelFormat)
    {
        Eyer::EyerAVRational videoTimebase;
        videoTimebase.num = 1;
        videoTimebase.den = fps;

        return InitVP9(width, height, videoTimebase, _pixelFormat);
    }

    int EyerAVEncoderParam::InitVP9(int _width, int _height, const EyerAVRational & _timebase, const EyerAVPixelFormat & _pixelFormat)
    {
        codecId         = EyerAVCodecID::CODEC_ID_VP9;
        width           = _width;
        height          = _height;
        timebase        = _timebase;
        pixelFormat     = _pixelFormat;
        return 0;
    }

    int EyerAVEncoderParam::InitVideo(EyerAVCodecID codecId, int width, int height, int fps, const EyerAVPixelFormat & pixelFormat)
    {
        Eyer::EyerAVRational videoTimebase;
        videoTimebase.num = 1;
        videoTimebase.den = fps;
        return InitVideo(codecId, width, height, videoTimebase, pixelFormat);
    }

    int EyerAVEncoderParam::InitVideo(EyerAVCodecID _codecId, int _width, int _height, const EyerAVRational & _timebase, const EyerAVPixelFormat & _pixelFormat)
    {
        codecId         = _codecId;
        width           = _width;
        height          = _height;
        timebase        = _timebase;
        pixelFormat     = _pixelFormat;
        return 0;
    }

    int EyerAVEncoderParam::InitAAC(EyerAVChannelLayout _channelLayout, EyerAVSampleFormat _sampleFormat, int _sample_rate)
    {
        codecId         = EyerAVCodecID::CODEC_ID_AAC;
        channelLayout   = _channelLayout;
        sample_rate     = _sample_rate;
        sampleFormat    = _sampleFormat;
        return 0;
    }

    int EyerAVEncoderParam::InitFDKAAC(EyerAVChannelLayout _channelLayout, EyerAVSampleFormat _sampleFormat, int _sample_rate)
    {
        codecId         = EyerAVCodecID::CODEC_ID_AAC;
        channelLayout   = _channelLayout;
        sample_rate     = _sample_rate;
        sampleFormat    = _sampleFormat;
        return 0;
    }

    int EyerAVEncoderParam::InitLibOpus(EyerAVChannelLayout _channelLayout, EyerAVSampleFormat _sampleFormat, int _sample_rate)
    {
        codecId         = EyerAVCodecID::CODEC_ID_LIB_OPUS;
        channelLayout   = _channelLayout;
        sample_rate     = _sample_rate;
        sampleFormat    = _sampleFormat;
        return 0;
    }

    int EyerAVEncoderParam::InitMP3(EyerAVChannelLayout _channelLayout, EyerAVSampleFormat _sampleFormat, int _sample_rate)
    {
        codecId         = EyerAVCodecID::CODEC_ID_MP3;
        channelLayout   = _channelLayout;
        sample_rate     = _sample_rate;
        sampleFormat    = _sampleFormat;
        return 0;
    }

    int EyerAVEncoderParam::InitFLAC(EyerAVChannelLayout _channelLayout, EyerAVSampleFormat _sampleFormat, int _sample_rate)
    {
        codecId         = EyerAVCodecID::CODEC_ID_FLAC;
        channelLayout   = _channelLayout;
        sample_rate     = _sample_rate;
        sampleFormat    = _sampleFormat;
        return 0;
    }

    int EyerAVEncoderParam::InitPCM_S16LE(EyerAVChannelLayout _channelLayout, EyerAVSampleFormat _sampleFormat, int _sample_rate)
    {
        codecId         = EyerAVCodecID::CODEC_ID_PCM_S16LE;
        channelLayout   = _channelLayout;
        sample_rate     = _sample_rate;
        sampleFormat    = _sampleFormat;
        return 0;
    }

    int EyerAVEncoderParam::InitPCM_S32LE(EyerAVChannelLayout _channelLayout, EyerAVSampleFormat _sampleFormat, int _sample_rate)
    {
        codecId         = EyerAVCodecID::CODEC_ID_PCM_S32LE;
        channelLayout   = _channelLayout;
        sample_rate     = _sample_rate;
        sampleFormat    = _sampleFormat;
        return 0;
    }

    int EyerAVEncoderParam::InitAudio(EyerAVCodecID _codecId, EyerAVChannelLayout _channelLayout, EyerAVSampleFormat _sampleFormat, int _sample_rate)
    {
        codecId         = _codecId;
        channelLayout   = _channelLayout;
        sample_rate     = _sample_rate;
        sampleFormat    = _sampleFormat;
        return 0;
    }

    int EyerAVEncoderParam::InitJPEG(int _width, int _height)
    {
        codecId         = EyerAVCodecID::CODEC_ID_MJPEG;
        width           = _width;
        height          = _height;
        EyerAVRational _timebase;
        _timebase.den = 25;
        _timebase.num = 1;
        timebase        = _timebase;

        return 0;
    }

    int EyerAVEncoderParam::InitPNG(int _width, int _height, const EyerAVPixelFormat & _pixelFormat)
    {
        codecId         = EyerAVCodecID::CODEC_ID_PNG;
        width           = _width;
        height          = _height;
        EyerAVRational _timebase;
        _timebase.den = 25;
        _timebase.num = 1;
        timebase        = _timebase;
        pixelFormat     = _pixelFormat;

        return 0;
    }

    int EyerAVEncoderParam::InitFromStream(const EyerAVStream & _straem)
    {
        // 264 和 264 都变成 264
        if(_straem.piml->codecpar->codec_id == AV_CODEC_ID_H264){
            codecId = EyerAVCodecID::CODEC_ID_H264;
        }
        else if(_straem.piml->codecpar->codec_id == AV_CODEC_ID_H265){
            codecId = EyerAVCodecID::CODEC_ID_H264;
        }
        else if(_straem.piml->codecpar->codec_id == AV_CODEC_ID_MJPEG){
            codecId = EyerAVCodecID::CODEC_ID_MJPEG;
        }
        else if(_straem.piml->codecpar->codec_id == AV_CODEC_ID_PNG){
            codecId = EyerAVCodecID::CODEC_ID_PNG;
        }
        else if(_straem.piml->codecpar->codec_id == AV_CODEC_ID_MP3){
            codecId = EyerAVCodecID::CODEC_ID_MP3;
        }
        else if(_straem.piml->codecpar->codec_id == AV_CODEC_ID_AAC){
            codecId = EyerAVCodecID::CODEC_ID_MP3;
        }
        else {
            EyerLog("Codec ID: %d\n", _straem.piml->codecpar->codec_id);
            if(_straem.piml->codecpar->codec_type == AVMediaType::AVMEDIA_TYPE_VIDEO){
                codecId = EyerAVCodecID::CODEC_ID_H264;
            }
            if(_straem.piml->codecpar->codec_type == AVMediaType::AVMEDIA_TYPE_AUDIO){
                codecId = EyerAVCodecID::CODEC_ID_MP3;
            }
        }
        return 0;
    }

    int EyerAVEncoderParam::SetTimebase(const EyerAVRational & _timebase)
    {
        timebase = _timebase;
        return 0;
    }

    int EyerAVEncoderParam::SetWH(int _width, int _height)
    {
        width = _width;
        height = _height;
        return 0;
    }
}