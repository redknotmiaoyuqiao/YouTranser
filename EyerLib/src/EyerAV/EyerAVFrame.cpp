#include "EyerAVFrame.hpp"

#include "EyerCore/EyerCore.hpp"

#include "EyerAVFramePrivate.hpp"
#include "EyerAVPixelFormat.hpp"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "EyerAVFrame_CVPixelBuffer.h"

namespace Eyer
{
    EyerAVFrame::EyerAVFrame()
    {
        piml = new EyerAVFramePrivate();
        piml->frame = av_frame_alloc();
    }

    EyerAVFrame::EyerAVFrame(void * _cvPixelBuffer)
        : EyerAVFrame()
    {
#ifdef EYER_PLATFORM_DARWIN
        cvPixelBuffer = copyCVPixelBuffer(_cvPixelBuffer);
        SetPixelFormat(Eyer::EyerAVPixelFormat::EYER_EXT_CVPIXELBUFFER);
#endif
    }

    EyerAVFrame::EyerAVFrame(const EyerAVFrame & frame) : EyerAVFrame()
    {
        *this = frame;
    }

    EyerAVFrame::~EyerAVFrame()
    {
#ifdef EYER_PLATFORM_DARWIN
        if(cvPixelBuffer != nullptr){
            freeCVPixelBuffer(cvPixelBuffer);
            cvPixelBuffer = nullptr;
        }
#endif

        av_frame_unref(piml->frame);
        av_frame_free(&piml->frame);

        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    EyerAVFrame & EyerAVFrame::operator = (const EyerAVFrame & frame)
    {
#ifdef EYER_PLATFORM_DARWIN
        if(cvPixelBuffer != nullptr){
            freeCVPixelBuffer(cvPixelBuffer);
            cvPixelBuffer = nullptr;
        }
        if(frame.cvPixelBuffer != nullptr){
            cvPixelBuffer = copyCVPixelBuffer(frame.cvPixelBuffer);
        }
#endif
        av_frame_unref(piml->frame);

        piml->secPTS = frame.piml->secPTS;
        piml->LAST_FRAME_FLAG = frame.piml->LAST_FRAME_FLAG;
        piml->angle = frame.piml->angle;
        av_frame_copy_props(piml->frame, frame.piml->frame);
        av_frame_copy(piml->frame, frame.piml->frame);
        av_frame_ref(piml->frame, frame.piml->frame);

        return *this;
    }

    int EyerAVFrame::SetPTS(int64_t pts)
    {
        piml->frame->pts = pts;
        return 0;
    }

    int64_t EyerAVFrame::GetPTS()
    {
        return piml->frame->pts;
    }

    double EyerAVFrame::GetSecPTS()
    {
        return piml->secPTS;
    }

    int EyerAVFrame::SetSecPTS(double pts)
    {
        piml->secPTS = pts;
        return 0;
    }

    const int EyerAVFrame::GetWidth() const
    {
        return piml->frame->width;
    }

    const int EyerAVFrame::GetHeight() const
    {
        return piml->frame->height;
    }

    int EyerAVFrame::SetWidth(int width)
    {
        piml->frame->width = width;
        return 0;
    }

    int EyerAVFrame::SetHeight(int height)
    {
        piml->frame->height = height;
        return 0;
    }

    int EyerAVFrame::SetPixelFormat(const EyerAVPixelFormat & pixelFormat)
    {
        piml->frame->format = pixelFormat.GetFFmpegId();
        return 0;
    }
    int EyerAVFrame::SetLinesize(int index, int linesize)
    {
        piml->frame->linesize[index] = linesize;
        return 0;
    }

    int EyerAVFrame::GetBuffer(int align)
    {
        av_frame_get_buffer(piml->frame, align);
        return 0;
    }

    int EyerAVFrame::SetVideoData420P(unsigned char * _y, unsigned char * _u, unsigned char * _v, int _width, int _height)
    {
        piml->frame->format = AVPixelFormat::AV_PIX_FMT_YUV420P;
        piml->frame->width = _width;
        piml->frame->height = _height;
        piml->frame->extended_data = piml->frame->data;

        av_frame_get_buffer(piml->frame, 16);
        for(int i=0; i<_height; i++){
            memcpy(piml->frame->data[0] + piml->frame->linesize[0] * i, _y + _width * i, _width);
        }

        for(int i=0; i<_height / 2; i++){
            memcpy(piml->frame->data[1] + piml->frame->linesize[1] * i, _u + _width / 2 * i, _width / 2);
            memcpy(piml->frame->data[2] + piml->frame->linesize[2] * i, _v + _width / 2 * i, _width / 2);
        }

        return 0;
    }

    int EyerAVFrame::Mirror(EyerAVFrame & frame, int type)
    {
        if(GetPixelFormat() != EyerAVPixelFormat::EYER_RGBA){
            frame = *this;
            return -1;
        }
        frame.piml->frame->width    = piml->frame->width;
        frame.piml->frame->height   = piml->frame->height;
        frame.piml->frame->format   = piml->frame->format;
        av_frame_get_buffer(frame.piml->frame, 1);

        int height = piml->frame->height;
        int width = piml->frame->width;

        if(type == 1){
            // 横向
            for(int i=0;i<height;i++){
                uint8_t * dist = frame.piml->frame->data[0] + frame.piml->frame->linesize[0] * i;
                uint8_t * src  = piml->frame->data[0] + piml->frame->linesize[0] * i;

                for(int j=0;j<width;j++){
                    memcpy(dist + (width - j) * 4, src + j * 4, 4);
                }
            }
        }
        else if(type == 2){
            for(int i=0;i<height;i++){
                uint8_t * dist = frame.piml->frame->data[0] + frame.piml->frame->linesize[0] * i;
                uint8_t * src  = piml->frame->data[0] + piml->frame->linesize[0] * (height - 1 - i);
                memcpy(dist, src, width * 4);
            }
        }
        else {
            for(int i=0;i<height;i++){
                uint8_t * dist = frame.piml->frame->data[0] + frame.piml->frame->linesize[0] * i;
                uint8_t * src  = piml->frame->data[0] + piml->frame->linesize[0] * i;
                memcpy(dist, src, width * 4);
            }
        }
        return 0;
    }

    int EyerAVFrame::SetAudioDataFLTP(uint8_t * data, int & offset)
    {
        piml->frame->channel_layout = AV_CH_LAYOUT_STEREO;
        piml->frame->channels = av_get_channel_layout_nb_channels(piml->frame->channel_layout);
        piml->frame->sample_rate = 44100;
        piml->frame->nb_samples = 1152;
        piml->frame->format = AVSampleFormat::AV_SAMPLE_FMT_FLTP;

        // int num_bytes = av_get_bytes_per_sample(AVSampleFormat::AV_SAMPLE_FMT_FLTP);
        // EyerLog("channels: %d\n", piml->frame->channels);

        av_frame_get_buffer(piml->frame, 16);

        int nb_samples = piml->frame->nb_samples;
        float * a = (float *)malloc(nb_samples * sizeof(float));
        for(int i=0;i<nb_samples;i++){
            a[i] = sin(i * (1.0 / nb_samples) * 2 * 3.1415926 * 8);
        }

        memcpy(piml->frame->data[0], a, nb_samples * sizeof(float));
        memcpy(piml->frame->data[1], a, nb_samples * sizeof(float));
        // memset(piml->frame->data[0], 0, piml->frame->linesize[0]);
        // memset(piml->frame->data[1], 0, piml->frame->linesize[0]);

        free(a);

        piml->frame->pts = offset;
        offset += piml->frame->nb_samples;
        // EyerLog("PTS: %d\n", piml->frame->pts);

        // memcpy(piml->frame->data[0], data, );

        return 0;
    }

    int EyerAVFrame::SetAudioDataS16_44100_2_1024 (uint8_t * data)
    {
        piml->frame->format         = AVSampleFormat::AV_SAMPLE_FMT_S16;
        piml->frame->sample_rate    = 44100;
        piml->frame->channels       = 2;
        piml->frame->nb_samples     = 1024;
        piml->frame->channel_layout = av_get_default_channel_layout(piml->frame->channels);

        av_frame_get_buffer(piml->frame, 16);

        // memset(piml->frame->data[0], 0, piml->frame->linesize[0]);
        memcpy(piml->frame->data[0], data, 2 * 2 * 1024);

        return 0;
    }

    int EyerAVFrame::InitVideoData(EyerAVPixelFormat pixelFormat, int width, int height)
    {
        piml->frame->format         = (AVPixelFormat)pixelFormat.GetFFmpegId();
        piml->frame->width          = width;
        piml->frame->height         = height;
        av_frame_get_buffer(piml->frame, 1);

        return 0;
    }

    int EyerAVFrame::InitAudioData(EyerAVChannelLayout channelLayout, EyerAVSampleFormat sampleFormat, int sample_rate, int nb_samples)
    {
        piml->frame->format         = (AVSampleFormat)sampleFormat.ffmpegId;
        piml->frame->sample_rate    = sample_rate;
        piml->frame->channel_layout = channelLayout.GetFFmpegId();
        piml->frame->channels       = av_get_channel_layout_nb_channels(piml->frame->channel_layout);
        piml->frame->nb_samples     = nb_samples;

        av_frame_get_buffer(piml->frame, 16);

        for(int i=0;i<8;i++){
            memset(piml->frame->data[i], 0, piml->frame->linesize[i]);
        }

        return 0;
    }

    int EyerAVFrame::Resample(EyerAVFrame & dstFrame, EyerAVChannelLayout channelLayout, EyerAVSampleFormat sampleFormat, int sample_rate)
    {
        av_frame_copy_props(dstFrame.piml->frame, piml->frame);

        dstFrame.piml->frame->channel_layout    = channelLayout.GetFFmpegId();
        dstFrame.piml->frame->channels          = av_get_channel_layout_nb_channels(dstFrame.piml->frame->channel_layout);
        dstFrame.piml->frame->sample_rate       = sample_rate;
        dstFrame.piml->frame->format            = sampleFormat.ffmpegId;

        av_frame_get_buffer(dstFrame.piml->frame, 1);

        SwrContext * swrCtx = swr_alloc_set_opts(
                NULL,
                dstFrame.piml->frame->channel_layout,
                (AVSampleFormat)dstFrame.piml->frame->format,
                dstFrame.piml->frame->sample_rate,

                piml->frame->channel_layout,
                (AVSampleFormat)piml->frame->format,
                piml->frame->sample_rate,

                0,
                NULL
        );

        swr_init(swrCtx);

        int ret = swr_convert_frame(swrCtx, dstFrame.piml->frame, piml->frame);

        swr_free(&swrCtx);

        return ret;
    }

    int EyerAVFrame::Scale(EyerAVFrame & frame, const EyerAVPixelFormat format) const
    {
        return Scale(frame, format, GetWidth(), GetHeight());
    }

    int EyerAVFrame::Scale(EyerAVFrame & dstFrame, const int dstW, const int dstH) const
    {
        AVPixelFormat distFormat = (AVPixelFormat)piml->frame->format;

        av_frame_copy_props(dstFrame.piml->frame, piml->frame);

        dstFrame.piml->frame->pict_type = AVPictureType::AV_PICTURE_TYPE_NONE;

        dstFrame.piml->frame->format    = distFormat;
        dstFrame.piml->frame->width     = dstW;
        dstFrame.piml->frame->height    = dstH;

        dstFrame.piml->secPTS           = piml->secPTS;

        // uint8_t
        av_frame_get_buffer(dstFrame.piml->frame, 1);

        int srcW = GetWidth();
        int srcH = GetHeight();
        AVPixelFormat srcFormat = (AVPixelFormat)(piml->frame->format);

        SwsContext * swsContext = sws_getContext(srcW, srcH, srcFormat, dstW, dstH, distFormat, SWS_SINC, NULL, NULL, NULL);

        if(swsContext == nullptr){
            return -1;
        }

        sws_scale(
                swsContext,
                piml->frame->data,
                piml->frame->linesize,
                0,
                srcH,

                dstFrame.piml->frame->data,
                dstFrame.piml->frame->linesize
        );

        sws_freeContext(swsContext);

        return 0;
    }

    int EyerAVFrame::Scale(EyerAVFrame & dstFrame, const EyerAVPixelFormat distformat, int dstW, int dstH) const
    {
        EyerAVPixelFormat format = distformat;
        if(distformat == EyerAVPixelFormat::EYER_KEEP_SAME){
            format = GetPixelFormat();
        }
        if(dstW <= 0){
            dstW = GetWidth();
        }
        if(dstH <= 0){
            dstH = GetHeight();
        }

        if(format == GetPixelFormat() && dstW == GetWidth() && dstH == GetHeight()){
            dstFrame = *this;
            return 0;
        }

        AVPixelFormat distFormat = (AVPixelFormat)format.GetFFmpegId();

        av_frame_copy_props(dstFrame.piml->frame, piml->frame);

        dstFrame.piml->frame->pict_type = AVPictureType::AV_PICTURE_TYPE_NONE;

        dstFrame.piml->frame->format    = distFormat;
        dstFrame.piml->frame->width     = dstW;
        dstFrame.piml->frame->height    = dstH;

        dstFrame.piml->secPTS           = piml->secPTS;

        // uint8_t
        av_frame_get_buffer(dstFrame.piml->frame, 1);

        int srcW = GetWidth();
        int srcH = GetHeight();
        AVPixelFormat srcFormat = (AVPixelFormat)(piml->frame->format);

        SwsContext * swsContext = sws_getContext(srcW, srcH, srcFormat, dstW, dstH, distFormat, SWS_SINC, NULL, NULL, NULL);

        if(swsContext == nullptr){
            return -1;
        }

        sws_scale(
                swsContext,
                piml->frame->data,
                piml->frame->linesize,
                0,
                srcH,

                dstFrame.piml->frame->data,
                dstFrame.piml->frame->linesize
        );

        sws_freeContext(swsContext);

        return 0;
    }

    uint8_t * EyerAVFrame::GetData(int index) const
    {
        return piml->frame->data[index];
    }

    const int EyerAVFrame::GetLinesize(int index) const
    {
        return piml->frame->linesize[index];
    }

    int EyerAVFrame::GetSampleRate()
    {
        return piml->frame->sample_rate;
    }

    const EyerAVPixelFormat EyerAVFrame::GetPixelFormat() const
    {
        return EyerAVPixelFormat::GetByFFmpegId(piml->frame->format);
    }

    EyerAVChannelLayout EyerAVFrame::GetChannelLayout()
    {
        return EyerAVChannelLayout::GetByFFmpegId(piml->frame->channel_layout);
    }

    EyerAVSampleFormat EyerAVFrame::GetSampleFormat()
    {
        return EyerAVSampleFormat::GetByFFmpegId(piml->frame->format);
    }

    int EyerAVFrame::GetSampleNB()
    {
        return piml->frame->nb_samples;
    }

    int EyerAVFrame::SetSampleRate(int sampleRate)
    {
        piml->frame->sample_rate = sampleRate;
        return 0;
    }

    int EyerAVFrame::SetChannelLayout(EyerAVChannelLayout channelLayout)
    {
        piml->frame->channel_layout = channelLayout.GetFFmpegId();
        piml->frame->channels = av_get_channel_layout_nb_channels(piml->frame->channel_layout);
        return 0;
    }

    int EyerAVFrame::SetSampleFormat(EyerAVSampleFormat sampleFormat)
    {
        piml->frame->format = sampleFormat.ffmpegId;
        return 0;
    }

    int EyerAVFrame::SetSampleNB(int sampleNB)
    {
        piml->frame->nb_samples = sampleNB;
        return 0;
    }

    bool EyerAVFrame::GetLastFrameFlag()
    {
        return piml->LAST_FRAME_FLAG;
    }

    int EyerAVFrame::SetLastFrameFlag(bool flag)
    {
        piml->LAST_FRAME_FLAG = flag;
        return 0;
    }

    const int EyerAVFrame::GetAngle() const
    {
        return piml->angle;
    }
}