#include "EyerAVTranscoderSupport.hpp"

#include "EyerAV/EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    std::vector<EyerAVFileFmt> EyerAVTranscoderSupport::QuerySupportFmt()
    {
        std::vector<EyerAVFileFmt> supportList;
        supportList.push_back(EyerAVFileFmt::MP4);
        supportList.push_back(EyerAVFileFmt::MOV);
        return supportList;
    }

    std::vector<EyerAVCodecID> EyerAVTranscoderSupport::QuerySupportVideoCodec(const EyerAVFileFmt & fileFmt)
    {
        std::vector<EyerAVCodecID> supportList;
        if(fileFmt == EyerAVFileFmt::MP4){
            supportList.push_back(EyerAVCodecID::CODEC_ID_H264);
            supportList.push_back(EyerAVCodecID::CODEC_ID_H265);
        }
        if(fileFmt == EyerAVFileFmt::MOV){
            supportList.push_back(EyerAVCodecID::CODEC_ID_H264);
            supportList.push_back(EyerAVCodecID::CODEC_ID_H265);
        }
        return supportList;
    }

    std::vector<EyerAVCodecID> EyerAVTranscoderSupport::QuerySupportAudioCodec(const EyerAVFileFmt & fileFmt)
    {
        std::vector<EyerAVCodecID> supportList;
        if(fileFmt == EyerAVFileFmt::MP4) {
            supportList.push_back(EyerAVCodecID::CODEC_ID_AAC);
            supportList.push_back(EyerAVCodecID::CODEC_ID_MP3);
            supportList.push_back(EyerAVCodecID::CODEC_ID_PCM_S16LE);
        }
        else if(fileFmt == EyerAVFileFmt::MOV) {
            supportList.push_back(EyerAVCodecID::CODEC_ID_AAC);
            supportList.push_back(EyerAVCodecID::CODEC_ID_MP3);
            supportList.push_back(EyerAVCodecID::CODEC_ID_PCM_S16LE);
        }
        return supportList;
    }

    std::vector<EyerAVPixelFormat> EyerAVTranscoderSupport::QuerySupportPixelFormat(const EyerAVCodecID & codecId)
    {
        std::vector<EyerAVPixelFormat> supportList;
        supportList.push_back(EyerAVPixelFormat::EYER_KEEP_SAME);
        if(codecId == EyerAVCodecID::CODEC_ID_H264){
            const AVCodec * codec = avcodec_find_encoder_by_name("libx264");
            const AVPixelFormat *pfmt = codec->pix_fmts;
            while (pfmt != NULL && *pfmt  != AV_PIX_FMT_NONE) {
                EyerAVPixelFormat format = EyerAVPixelFormat::GetByFFmpegId(*pfmt);
                if(format == EyerAVPixelFormat::EYER_NV20LE){
                    pfmt++;
                    continue;
                }
                if(format == EyerAVPixelFormat::EYER_NV16){
                    pfmt++;
                    continue;
                }
                if(format == EyerAVPixelFormat::EYER_YUVJ420P){
                    pfmt++;
                    continue;
                }
                if(format == EyerAVPixelFormat::EYER_YUVJ422P){
                    pfmt++;
                    continue;
                }
                if(format == EyerAVPixelFormat::EYER_YUVJ444P){
                    pfmt++;
                    continue;
                }

                supportList.push_back(format);
                pfmt++;
            }
        }
        if(codecId == EyerAVCodecID::CODEC_ID_H265){
            const AVCodec * codec = avcodec_find_encoder_by_name("libx265");
            const AVPixelFormat *pfmt = codec->pix_fmts;
            while (pfmt != NULL && *pfmt  != AV_PIX_FMT_NONE) {
                EyerAVPixelFormat format = EyerAVPixelFormat::GetByFFmpegId(*pfmt);
                if(format == EyerAVPixelFormat::EYER_YUVJ420P){
                    pfmt++;
                    continue;
                }
                if(format == EyerAVPixelFormat::EYER_YUVJ422P){
                    pfmt++;
                    continue;
                }
                if(format == EyerAVPixelFormat::EYER_YUVJ444P){
                    pfmt++;
                    continue;
                }
                supportList.push_back(format);
                pfmt++;
            }
        }
        return supportList;
    }

    std::vector<EyerAVChannelLayout> EyerAVTranscoderSupport::QuerySupportChannelLayout(const EyerAVCodecID & codecId)
    {
        AVCodec * codec = NULL;
        if(codecId == EyerAVCodecID::CODEC_ID_AAC){
            codec = avcodec_find_encoder_by_name("libfdk_aac");
        }
        else if(codecId == EyerAVCodecID::CODEC_ID_MP3){
            codec = avcodec_find_encoder((AVCodecID)codecId.GetFFmpegId());
        }
        else if(codecId == EyerAVCodecID::CODEC_ID_PCM_S16LE){
            codec = avcodec_find_encoder((AVCodecID)codecId.GetFFmpegId());
        }
        else {
            return std::vector<EyerAVChannelLayout>();
        }

        std::vector<EyerAVChannelLayout> supportList;
        supportList.push_back(EyerAVChannelLayout::EYER_KEEP_SAME);

        const uint64_t * p_channel_layout = codec->channel_layouts;
        if(p_channel_layout == NULL){
            std::vector<EyerAVChannelLayout> layouts = EyerAVChannelLayout::ListAllAVChannelLayout();
            for(int i=0;i<layouts.size();i++){
                supportList.push_back(layouts[i]);
            }
        }
        else {
            while (*p_channel_layout != NULL) {
                EyerAVChannelLayout channelLayout = EyerAVChannelLayout::GetByFFmpegId(*p_channel_layout);
                supportList.push_back(channelLayout);
                p_channel_layout++;
            }
        }

        return supportList;
    }

    std::vector<int> EyerAVTranscoderSupport::QuerySupportSampleRate(const EyerAVCodecID & codecId)
    {
        std::vector<int> supportList;
        supportList.push_back(-2);
        AVCodec * codec = NULL;
        if(codecId == EyerAVCodecID::CODEC_ID_AAC){
            codec = avcodec_find_encoder_by_name("libfdk_aac");
        }
        else if(codecId == EyerAVCodecID::CODEC_ID_MP3) {
            codec = avcodec_find_encoder((AVCodecID)codecId.GetFFmpegId());
        }
        else if(codecId == EyerAVCodecID::CODEC_ID_PCM_S16LE) {
            codec = avcodec_find_encoder((AVCodecID)codecId.GetFFmpegId());
        }
        else {
            return std::vector<int>();
        }

        const int * supported_samplerates = codec->supported_samplerates;
        if(supported_samplerates == NULL){
            supportList.push_back(96000);
            supportList.push_back(88200);
            supportList.push_back(64000);
            supportList.push_back(48000);
            supportList.push_back(44100);
            supportList.push_back(32000);
            supportList.push_back(24000);
            supportList.push_back(22050);
            supportList.push_back(16000);
            supportList.push_back(12000);
            supportList.push_back(11025);
            supportList.push_back(8000);
        }
        else {
            while (*supported_samplerates != NULL) {
                supportList.push_back(*supported_samplerates);
                supported_samplerates++;
            }
        }

        return supportList;
    }

    EyerAVSampleFormat EyerAVTranscoderSupport::GetHighestSampleFmt(const EyerAVCodecID & codecId)
    {
        if(codecId == EyerAVCodecID::CODEC_ID_AAC){
            return EyerAVSampleFormat::SAMPLE_FMT_S16;
        }
        else if(codecId == EyerAVCodecID::CODEC_ID_MP3){
            return EyerAVSampleFormat::SAMPLE_FMT_S32P;
        }
        else if(codecId == EyerAVCodecID::CODEC_ID_PCM_S16LE){
            return EyerAVSampleFormat::SAMPLE_FMT_S16;
        }
        return EyerAVSampleFormat::UNKNOW;
    }

    bool EyerAVTranscoderSupport::IsPixelFmtSupports(const EyerAVCodecID & codecId, const EyerAVPixelFormat & pixfmt)
    {
        if(codecId == EyerAVCodecID::CODEC_ID_H264) {
            const AVCodec *codec = avcodec_find_encoder_by_name("libx264");
            const AVPixelFormat *pfmt = codec->pix_fmts;
            while (pfmt != NULL && *pfmt != AV_PIX_FMT_NONE) {
                EyerAVPixelFormat format = EyerAVPixelFormat::GetByFFmpegId(*pfmt);
                if(format == pixfmt){
                    return true;
                }
                pfmt++;
            }
        }
        else if(codecId == EyerAVCodecID::CODEC_ID_H265){
            const AVCodec *codec = avcodec_find_encoder_by_name("libx265");
            const AVPixelFormat *pfmt = codec->pix_fmts;
            while (pfmt != NULL && *pfmt != AV_PIX_FMT_NONE) {
                EyerAVPixelFormat format = EyerAVPixelFormat::GetByFFmpegId(*pfmt);
                if(format == pixfmt){
                    return true;
                }
                pfmt++;
            }
        }
        return false;
    }

    bool EyerAVTranscoderSupport::IsAudioChannelSupports(const EyerAVCodecID & codecId, const EyerAVChannelLayout & audioChannel)
    {
        std::vector<EyerAVChannelLayout> audioChannels = QuerySupportChannelLayout(codecId);
        for(int i=0; i<audioChannels.size(); i++){
            EyerAVChannelLayout layout = audioChannels[i];
            if(layout == EyerAVChannelLayout::EYER_KEEP_SAME){
                continue;
            }
            if(layout == audioChannel){
                return true;
            }
        }
        return false;
    }

    bool EyerAVTranscoderSupport::IsSampleRateSupports(const EyerAVCodecID & codecId, int sampleRate)
    {
        std::vector<int> sampleRates = QuerySupportSampleRate(codecId);
        for(int i=0; i<sampleRates.size(); i++){
            int sr = sampleRates[i];
            if(sr == -2){
                return true;
            }
            if(sr == sampleRate){
                return true;
            }
        }
        return false;
    }
}