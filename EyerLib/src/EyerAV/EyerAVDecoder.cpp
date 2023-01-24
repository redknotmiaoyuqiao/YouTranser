#include "EyerAVDecoder.hpp"

#include "EyerAVDecoderPrivate.hpp"
#include "EyerAVStreamPrivate.hpp"
#include "EyerAVPacketPrivate.hpp"
#include "EyerAVFramePrivate.hpp"

#include "EyerAVPacket.hpp"
#include "EyerAVFrame.hpp"

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

    int EyerAVDecoder::Init(const EyerAVStream & stream, int threadnum)
    {
        piml->streamTimebase = stream.piml->timebase;
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
            codec = avcodec_find_decoder_by_name("libopenh264");
        }
        */
        else {
            codec = avcodec_find_decoder(piml->codecContext->codec_id);
        }
        piml->codecContext->thread_count = threadnum;
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
}