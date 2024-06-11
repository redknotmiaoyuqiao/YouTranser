#include "EyerAVDecoder.hpp"

#include "EyerAVDecoderPrivate.hpp"
#include "EyerAVStreamPrivate.hpp"
#include "EyerAVPacketPrivate.hpp"
#include "EyerAVFramePrivate.hpp"

#include "EyerAVPacket.hpp"
#include "EyerAVFrame.hpp"


static enum AVPixelFormat get_hw_format(AVCodecContext *ctx,
                                        const enum AVPixelFormat *pix_fmts)
{
    const enum AVPixelFormat *p;

    for (p = pix_fmts; *p != -1; p++) {
        EyerLog("*p: %d %d\n", *p, AV_PIX_FMT_YUV422P10LE);
        if (*p == AV_PIX_FMT_D3D11VA_VLD)
            return *p;
    }
    return AV_PIX_FMT_NONE;
}

namespace Eyer
{
    EyerAVDecoder::EyerAVDecoder()
    {
        piml = new EyerAVDecoderPrivate();
        piml->codecContext = avcodec_alloc_context3(nullptr);
    }

    EyerAVDecoder::~EyerAVDecoder()
    {
        if(piml->codecContext != nullptr){
            avcodec_free_context(&piml->codecContext);
            piml->codecContext = nullptr;
        }
        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    int EyerAVDecoder::Init(const EyerAVStream & stream, int threadnum, EyerAVDecoderOption option)
    {
        piml->angle = stream.GetAngle();
        piml->streamTimebase = stream.piml->timebase;
        // EyerLog("num: %d, den: %d\n", stream.piml->timebase.num, stream.piml->timebase.den);
        avcodec_parameters_to_context(piml->codecContext, stream.piml->codecpar);

        const AVCodec * codec = nullptr;
        if(piml->codecContext->codec_id == AV_CODEC_ID_VP9){
            codec = avcodec_find_decoder_by_name("libvpx-vp9");
        }
        else if(piml->codecContext->codec_id == AV_CODEC_ID_VP8){
            codec = avcodec_find_decoder_by_name("libvpx");
        }

        /*
        else if(piml->codecContext->codec_id == AV_CODEC_ID_H264){
            // codec = avcodec_find_decoder(piml->codecContext->codec_id);
            // codec = avcodec_find_decoder_by_name("libopenh264");
            codec = avcodec_find_decoder_by_name("h264_d3d11va");
        }
        */
        else {
            codec = avcodec_find_decoder(piml->codecContext->codec_id);
        }
        piml->codecContext->thread_count = threadnum;

        if(option == EyerAVDecoderOption::D3D11VA) {
            AVBufferRef* hw_device_ctx = nullptr;
            av_hwdevice_ctx_create(&hw_device_ctx, AVHWDeviceType::AV_HWDEVICE_TYPE_D3D11VA, NULL, NULL, NULL);
            if (hw_device_ctx) {
                piml->codecContext->hw_device_ctx = hw_device_ctx;
            }
            else {
                EyerLog("Init D3D11VA Error\n");
            }
        }

        if(piml->codecContext->codec_id == AV_CODEC_ID_H264) {
            /*
            AVBufferRef* hw_device_ctx = nullptr;
            av_hwdevice_ctx_create(&hw_device_ctx, AVHWDeviceType::AV_HWDEVICE_TYPE_D3D11VA, NULL, NULL, NULL);
            if (hw_device_ctx) {
                piml->codecContext->hw_device_ctx = av_buffer_ref(hw_device_ctx);
            }
             */
        }

       //  EyerLog("Codec Name: %d %d\n", piml->codecContext->codec_id, AV_CODEC_ID_PNG);

        int ret = avcodec_open2(piml->codecContext, codec, nullptr);
        return ret;
    }

    int EyerAVDecoder::SendPacket(EyerAVPacket * packet)
    {
        return avcodec_send_packet(piml->codecContext, packet->piml->packet);
    }

    int EyerAVDecoder::SendPacket(EyerAVPacket & packet)
    {
        return avcodec_send_packet(piml->codecContext, packet.piml->packet);
    }

    int EyerAVDecoder::SendPacket(EyerSmartPtr<EyerAVPacket> & packet)
    {
        return avcodec_send_packet(piml->codecContext, packet->piml->packet);
    }

    int EyerAVDecoder::SendPacketNull()
    {
        return avcodec_send_packet(piml->codecContext, nullptr);
    }

    int EyerAVDecoder::RecvFrame(EyerAVFrame & frame)
    {
        int ret = avcodec_receive_frame(piml->codecContext, frame.piml->frame);
        if(!ret){
            int64_t pts = frame.GetPTS();
            frame.piml->secPTS = pts * (double)piml->streamTimebase.num / piml->streamTimebase.den;
            frame.piml->angle = GetAngle();
        }
        return ret;
    }

    EyerSmartPtr<EyerAVFrame> EyerAVDecoder::RecvFrame(int & ret)
    {
        EyerAVFrame * avFrame = new EyerAVFrame();
        EyerSmartPtr<EyerAVFrame> frame(avFrame);

        ret = RecvFrame(*avFrame);

        return frame;
    }

    int EyerAVDecoder::GetTimebase(EyerAVRational & timebase)
    {
        timebase.num = piml->codecContext->time_base.num;
        timebase.den = piml->codecContext->time_base.den;
        return 0;
    }

    int EyerAVDecoder::GetSampleRate()
    {
        return piml->codecContext->sample_rate;
    }

    EyerAVChannelLayout EyerAVDecoder::GetAVChannelLayout()
    {
        return EyerAVChannelLayout::GetByFFmpegId(piml->codecContext->channel_layout);
    }

    EyerAVSampleFormat EyerAVDecoder::GetAVSampleFormat()
    {
        return EyerAVSampleFormat::GetByFFmpegId(piml->codecContext->sample_fmt);
    }

    const int EyerAVDecoder::GetAngle() const
    {
        return piml->angle;
    }
}