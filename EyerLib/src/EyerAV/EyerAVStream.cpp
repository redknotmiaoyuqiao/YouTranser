#include "EyerAVStream.hpp"

#include "EyerAVStreamPrivate.hpp"
#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    EyerAVStream::EyerAVStream()
    {
        piml = new EyerAVStreamPrivate();
        piml->codecpar = avcodec_parameters_alloc();
    }

    EyerAVStream::~EyerAVStream()
    {
        if(piml->codecpar != nullptr){
            avcodec_parameters_free(&piml->codecpar);
            piml->codecpar = nullptr;
        }
        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    EyerAVStream::EyerAVStream(const EyerAVStream & stream)
        : EyerAVStream()
    {
        *this = stream;
    }

    EyerAVStream::EyerAVStream(EyerAVStream && stream)
    {
        piml = new EyerAVStreamPrivate();
        piml->codecpar = stream.piml->codecpar;
        piml->stream_id = stream.piml->stream_id;
        piml->duration = stream.piml->duration;
        stream.piml->codecpar = nullptr;
    }

    EyerAVStream & EyerAVStream::operator = (const EyerAVStream & stream)
    {
        avcodec_parameters_copy(piml->codecpar, stream.piml->codecpar);
        piml->timebase      = stream.piml->timebase;
        piml->stream_id     = stream.piml->stream_id;
        piml->duration      = stream.piml->duration;
        return *this;
    }

    const int EyerAVStream::GetStreamId() const
    {
        return piml->stream_id;
    }

    double EyerAVStream::GetDuration() const
    {
        return piml->duration;
    }

    const EyerAVMediaType EyerAVStream::GetType() const
    {
        return EyerAVMediaType::GetMediaTypeByFFmpegId(piml->codecpar->codec_type);
    }

    const int EyerAVStream::GetWidth() const
    {
        return piml->codecpar->width;
    }

    const int EyerAVStream::GetHeight() const
    {
        return piml->codecpar->height;
    }

    EyerAVRational EyerAVStream::GetTimebase()
    {
        EyerAVRational timebase;
        timebase.den = piml->timebase.den;
        timebase.num = piml->timebase.num;
        return timebase;
    }

    EyerAVCodecID EyerAVStream::GetCodecID()
    {
        if(piml->codecpar->codec_id == AV_CODEC_ID_H264){
            return EyerAVCodecID::CODEC_ID_H264;
        }
        else if(piml->codecpar->codec_id == AV_CODEC_ID_MP3){
            return EyerAVCodecID::CODEC_ID_MP3;
        }
        else if(piml->codecpar->codec_id == AV_CODEC_ID_AAC){
            return EyerAVCodecID::CODEC_ID_AAC;
        }
        else if(piml->codecpar->codec_id == AV_CODEC_ID_H265){
            return EyerAVCodecID::CODEC_ID_H265;
        }
        else if(piml->codecpar->codec_id == AV_CODEC_ID_PNG){
            return EyerAVCodecID::CODEC_ID_PNG;
        }
        else if(piml->codecpar->codec_id == AV_CODEC_ID_MJPEG){
            return EyerAVCodecID::CODEC_ID_MJPEG;
        }

        return EyerAVCodecID::CODEC_ID_UNKNOW;
    }

    EyerAVPixelFormat EyerAVStream::GetPixelFormat() const
    {
        return EyerAVPixelFormat::GetByFFmpegId(piml->codecpar->format);
    }

    EyerAVChannelLayout EyerAVStream::GetChannelLayout() const
    {
        return EyerAVChannelLayout::GetByFFmpegId(piml->codecpar->channel_layout);
    }

    int EyerAVStream::GetChannels() const
    {
        return piml->codecpar->channels;
    }

    EyerAVSampleFormat EyerAVStream::GetSampleFormat() const
    {
        return EyerAVSampleFormat::GetByFFmpegId(piml->codecpar->format);
    }

    int EyerAVStream::GetSampleRate() const
    {
        return piml->codecpar->sample_rate;
    }
}