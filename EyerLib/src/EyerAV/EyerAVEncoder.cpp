#include "EyerAVEncoder.hpp"

#include "EyerAVEncoderPrivate.hpp"
#include "EyerAVPacketPrivate.hpp"
#include "EyerAVFramePrivate.hpp"

#include "EyerCore/EyerCore.hpp"

#include "EyerAVADTSUtil.hpp"

namespace Eyer {
    EyerAVEncoder::EyerAVEncoder() {
        piml = new EyerAVEncoderPrivate();
    }

    EyerAVEncoder::~EyerAVEncoder() {
        if (piml->codecContext != nullptr) {
            if (avcodec_is_open(piml->codecContext)) {
                avcodec_close(piml->codecContext);
            }
            avcodec_free_context(&piml->codecContext);
            piml->codecContext = nullptr;
        }

        if (piml != nullptr) {
            delete piml;
            piml = nullptr;
        }
    }

    int EyerAVEncoder::Init(const EyerAVEncoderParam &param) {
        AVDictionary *dict = NULL;

        const AVCodec *codec = nullptr;
        if (param.codecId == EyerAVCodecID::CODEC_ID_H264) {
            // codec = avcodec_find_encoder(AV_CODEC_ID_H264);
            codec = avcodec_find_encoder_by_name("libx264");

            if (piml->codecContext != nullptr) {
                if (avcodec_is_open(piml->codecContext)) {
                    avcodec_close(piml->codecContext);
                }
                avcodec_free_context(&piml->codecContext);
                piml->codecContext = nullptr;

                return -1;
            }

            piml->codecContext = avcodec_alloc_context3(codec);

            piml->codecContext->codec_type = AVMEDIA_TYPE_VIDEO;
            piml->codecContext->pix_fmt = (AVPixelFormat)param.pixelFormat.GetFFmpegId();
            piml->codecContext->width = param.width;
            piml->codecContext->height = param.height;
            piml->codecContext->thread_count = param.threadnum;

            piml->codecContext->time_base.den = param.timebase.den;
            piml->codecContext->time_base.num = param.timebase.num;

            av_dict_set( &dict, "crf", EyerString::Number(param.crf).c_str(), 0);
        }


        if (param.codecId == EyerAVCodecID::CODEC_ID_H265) {
            codec = avcodec_find_encoder_by_name("libx265");

            if (piml->codecContext != nullptr) {
                if (avcodec_is_open(piml->codecContext)) {
                    avcodec_close(piml->codecContext);
                }
                avcodec_free_context(&piml->codecContext);
                piml->codecContext = nullptr;

                return -1;
            }

            piml->codecContext = avcodec_alloc_context3(codec);

            piml->codecContext->codec_type = AVMEDIA_TYPE_VIDEO;
            piml->codecContext->codec_tag = MKTAG('h', 'v', 'c', '1');;
            piml->codecContext->pix_fmt = (AVPixelFormat)param.pixelFormat.GetFFmpegId();
            piml->codecContext->width = param.width;
            piml->codecContext->height = param.height;
            piml->codecContext->thread_count = param.threadnum;

            piml->codecContext->time_base.den = param.timebase.den;
            piml->codecContext->time_base.num = param.timebase.num;

            av_dict_set( &dict, "crf", EyerString::Number(param.crf).c_str(), 0);
        }


        if (param.codecId == EyerAVCodecID::CODEC_ID_VP8) {
            codec = avcodec_find_encoder(AV_CODEC_ID_VP8);

            if (piml->codecContext != nullptr) {
                if (avcodec_is_open(piml->codecContext)) {
                    avcodec_close(piml->codecContext);
                }
                avcodec_free_context(&piml->codecContext);
                piml->codecContext = nullptr;

                return -1;
            }

            piml->codecContext = avcodec_alloc_context3(codec);

            piml->codecContext->codec_type = AVMEDIA_TYPE_VIDEO;
            piml->codecContext->pix_fmt = (AVPixelFormat)param.pixelFormat.GetFFmpegId();
            piml->codecContext->width = param.width;
            piml->codecContext->height = param.height;

            piml->codecContext->time_base.den = param.timebase.den;
            piml->codecContext->time_base.num = param.timebase.num;
        }


        if (param.codecId == EyerAVCodecID::CODEC_ID_VP9) {
            codec = avcodec_find_encoder(AV_CODEC_ID_VP9);

            if (piml->codecContext != nullptr) {
                if (avcodec_is_open(piml->codecContext)) {
                    avcodec_close(piml->codecContext);
                }
                avcodec_free_context(&piml->codecContext);
                piml->codecContext = nullptr;

                return -1;
            }

            piml->codecContext = avcodec_alloc_context3(codec);

            piml->codecContext->codec_type = AVMEDIA_TYPE_VIDEO;
            piml->codecContext->pix_fmt = (AVPixelFormat)param.pixelFormat.GetFFmpegId();
            piml->codecContext->width = param.width;
            piml->codecContext->height = param.height;

            piml->codecContext->thread_count = 32;
            piml->codecContext->time_base.den = param.timebase.den;
            piml->codecContext->time_base.num = param.timebase.num;
        }

        if (param.codecId == EyerAVCodecID::CODEC_ID_MJPEG) {
            codec = avcodec_find_encoder(AV_CODEC_ID_MJPEG);

            if (piml->codecContext != nullptr) {
                if (avcodec_is_open(piml->codecContext)) {
                    avcodec_close(piml->codecContext);
                }
                avcodec_free_context(&piml->codecContext);
                piml->codecContext = nullptr;

                return -1;
            }

            piml->codecContext = avcodec_alloc_context3(codec);

            piml->codecContext->codec_type = AVMEDIA_TYPE_VIDEO;
            piml->codecContext->pix_fmt = AV_PIX_FMT_YUVJ420P;
            piml->codecContext->width = param.width;
            piml->codecContext->height = param.height;

            piml->codecContext->time_base.den = param.timebase.den;
            piml->codecContext->time_base.num = param.timebase.num;
        }

        if (param.codecId == EyerAVCodecID::CODEC_ID_PNG) {
            codec = avcodec_find_encoder(AV_CODEC_ID_PNG);

            if (piml->codecContext != nullptr) {
                if (avcodec_is_open(piml->codecContext)) {
                    avcodec_close(piml->codecContext);
                }
                avcodec_free_context(&piml->codecContext);
                piml->codecContext = nullptr;

                return -1;
            }

            piml->codecContext = avcodec_alloc_context3(codec);

            piml->codecContext->codec_type = AVMEDIA_TYPE_VIDEO;
            piml->codecContext->pix_fmt = (AVPixelFormat)param.pixelFormat.GetFFmpegId();
            piml->codecContext->width = param.width;
            piml->codecContext->height = param.height;

            piml->codecContext->time_base.den = param.timebase.den;
            piml->codecContext->time_base.num = param.timebase.num;
        }

        if (param.codecId == EyerAVCodecID::CODEC_ID_AAC) {
            // codec = avcodec_find_encoder(AV_CODEC_ID_AAC);
            codec = avcodec_find_encoder_by_name("libfdk_aac");

            if (piml->codecContext != nullptr) {
                if (avcodec_is_open(piml->codecContext)) {
                    avcodec_close(piml->codecContext);
                }
                avcodec_free_context(&piml->codecContext);
                piml->codecContext = nullptr;

                return -1;
            }

            piml->codecContext = avcodec_alloc_context3(codec);

            piml->codecContext->codec_type = AVMEDIA_TYPE_AUDIO;
            piml->codecContext->sample_fmt = (AVSampleFormat)param.sampleFormat.ffmpegId;

            piml->codecContext->sample_rate = param.sample_rate;

            piml->codecContext->channel_layout = param.channelLayout.GetFFmpegId();
            piml->codecContext->channels = av_get_channel_layout_nb_channels(piml->codecContext->channel_layout);

            piml->codecContext->time_base.den = param.sample_rate;
            piml->codecContext->time_base.num = 1;
        }

        if (param.codecId == EyerAVCodecID::CODEC_ID_LIB_OPUS) {
            // codec = avcodec_find_encoder(AV_CODEC_ID_AAC);
            codec = avcodec_find_encoder_by_name("libopus");

            if (piml->codecContext != nullptr) {
                if (avcodec_is_open(piml->codecContext)) {
                    avcodec_close(piml->codecContext);
                }
                avcodec_free_context(&piml->codecContext);
                piml->codecContext = nullptr;

                return -1;
            }

            piml->codecContext = avcodec_alloc_context3(codec);

            piml->codecContext->codec_type = AVMEDIA_TYPE_AUDIO;
            piml->codecContext->sample_fmt = (AVSampleFormat)param.sampleFormat.ffmpegId;

            piml->codecContext->sample_rate = param.sample_rate;

            piml->codecContext->channel_layout = param.channelLayout.GetFFmpegId();
            piml->codecContext->channels = av_get_channel_layout_nb_channels(piml->codecContext->channel_layout);

            piml->codecContext->time_base.den = param.sample_rate;
            piml->codecContext->time_base.num = 1;
        }

        if (param.codecId == EyerAVCodecID::CODEC_ID_MP3) {
            codec = avcodec_find_encoder(AV_CODEC_ID_MP3);

            if (piml->codecContext != nullptr) {
                if (avcodec_is_open(piml->codecContext)) {
                    avcodec_close(piml->codecContext);
                }
                avcodec_free_context(&piml->codecContext);
                piml->codecContext = nullptr;

                return -1;
            }

            piml->codecContext = avcodec_alloc_context3(codec);

            piml->codecContext->codec_type = AVMEDIA_TYPE_AUDIO;
            piml->codecContext->sample_fmt = (AVSampleFormat)param.sampleFormat.ffmpegId;

            piml->codecContext->sample_rate = param.sample_rate;

            piml->codecContext->channel_layout = param.channelLayout.GetFFmpegId();
            piml->codecContext->channels = av_get_channel_layout_nb_channels(piml->codecContext->channel_layout);
        }

        if (param.codecId == EyerAVCodecID::CODEC_ID_FLAC) {
            codec = avcodec_find_encoder(AV_CODEC_ID_FLAC);

            if (piml->codecContext != nullptr) {
                if (avcodec_is_open(piml->codecContext)) {
                    avcodec_close(piml->codecContext);
                }
                avcodec_free_context(&piml->codecContext);
                piml->codecContext = nullptr;

                return -1;
            }

            piml->codecContext = avcodec_alloc_context3(codec);

            piml->codecContext->codec_type = AVMEDIA_TYPE_AUDIO;
            piml->codecContext->sample_fmt = (AVSampleFormat)param.sampleFormat.ffmpegId;

            piml->codecContext->sample_rate = param.sample_rate;

            piml->codecContext->channel_layout = param.channelLayout.GetFFmpegId();
            piml->codecContext->channels = av_get_channel_layout_nb_channels(piml->codecContext->channel_layout);
        }


        if (param.codecId == EyerAVCodecID::CODEC_ID_PCM_S16LE) {
            codec = avcodec_find_encoder(AV_CODEC_ID_PCM_S16LE);

            if (piml->codecContext != nullptr) {
                if (avcodec_is_open(piml->codecContext)) {
                    avcodec_close(piml->codecContext);
                }
                avcodec_free_context(&piml->codecContext);
                piml->codecContext = nullptr;

                return -1;
            }

            piml->codecContext = avcodec_alloc_context3(codec);

            piml->codecContext->codec_type = AVMEDIA_TYPE_AUDIO;
            piml->codecContext->sample_fmt = (AVSampleFormat)param.sampleFormat.ffmpegId;

            piml->codecContext->sample_rate = param.sample_rate;

            piml->codecContext->channel_layout = param.channelLayout.GetFFmpegId();
            piml->codecContext->channels = av_get_channel_layout_nb_channels(piml->codecContext->channel_layout);
        }
        if (param.codecId == EyerAVCodecID::CODEC_ID_PCM_S32LE) {
            codec = avcodec_find_encoder(AV_CODEC_ID_PCM_S32LE);

            if (piml->codecContext != nullptr) {
                if (avcodec_is_open(piml->codecContext)) {
                    avcodec_close(piml->codecContext);
                }
                avcodec_free_context(&piml->codecContext);
                piml->codecContext = nullptr;

                return -1;
            }

            piml->codecContext = avcodec_alloc_context3(codec);

            piml->codecContext->codec_type = AVMEDIA_TYPE_AUDIO;
            piml->codecContext->sample_fmt = (AVSampleFormat)param.sampleFormat.ffmpegId;

            piml->codecContext->sample_rate = param.sample_rate;

            piml->codecContext->channel_layout = param.channelLayout.GetFFmpegId();
            piml->codecContext->channels = av_get_channel_layout_nb_channels(piml->codecContext->channel_layout);
        }

        int ret = avcodec_open2(piml->codecContext, codec, &dict);

        return ret;
    }

    int EyerAVEncoder::GetFrameSize()
    {
        return piml->codecContext->frame_size;
    }

    int EyerAVEncoder::SendFrame(EyerAVFrame &frame)
    {
        // frame.piml->frame->pict_type = AV_PICTURE_TYPE_I;
        return avcodec_send_frame(piml->codecContext, frame.piml->frame);
    }

    int EyerAVEncoder::SendFrameNull()
    {
        return avcodec_send_frame(piml->codecContext, nullptr);
    }

    int EyerAVEncoder::RecvPacket(EyerAVPacket &packet)
    {
        return avcodec_receive_packet(piml->codecContext, packet.piml->packet);
    }

    int EyerAVEncoder::GetTimebase(EyerAVRational &timebase)
    {
        timebase.num = piml->codecContext->time_base.num;
        timebase.den = piml->codecContext->time_base.den;
        return 0;
    }

    EyerAVRational EyerAVEncoder::GetTimebase()
    {
        EyerAVRational timebase;
        GetTimebase(timebase);
        return timebase;
    }

    EyerAVMediaType EyerAVEncoder::GetMediaType()
    {
        return EyerAVMediaType::GetMediaTypeByFFmpegId(piml->codecContext->codec_type);
    }

    EyerAVChannelLayout EyerAVEncoder::GetChannelLayout()
    {
        return EyerAVChannelLayout::GetByFFmpegId(piml->codecContext->channel_layout);
    }

    EyerAVSampleFormat EyerAVEncoder::GetSampleFormat()
    {
        return EyerAVSampleFormat::GetByFFmpegId(piml->codecContext->sample_fmt);
    }

    int EyerAVEncoder::GetSampleRate()
    {
        return piml->codecContext->sample_rate;
    }

    EyerAVADTS EyerAVEncoder::GetADTS(int packetSize)
    {
        EyerAVADTSUtil adtsUtil;
        EyerAVADTS avadts = adtsUtil.GetADTS(piml->codecContext->extradata, piml->codecContext->extradata_size, packetSize);

        return avadts;
    }

    EyerAVMediaType EyerAVEncoder::GetCodecType()
    {
        return EyerAVMediaType::GetMediaTypeByFFmpegId(piml->codecContext->codec_type);
    }
}
