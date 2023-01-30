#include "EyerAVCodecID.hpp"

#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    EyerAVCodecID EyerAVCodecID::CODEC_ID_UNKNOW    (AV_CODEC_ID_NONE + 10000, AV_CODEC_ID_NONE, "AV_CODEC_ID_NONE", "unknow");
    EyerAVCodecID EyerAVCodecID::CODEC_ID_H264      (AV_CODEC_ID_H264 + 10000, AV_CODEC_ID_H264, "AV_CODEC_ID_H264", "H.264/AVC");
    EyerAVCodecID EyerAVCodecID::CODEC_ID_H265      (AV_CODEC_ID_H265 + 10000, AV_CODEC_ID_H265, "AV_CODEC_ID_H265", "H.265/HEVC");
    EyerAVCodecID EyerAVCodecID::CODEC_ID_VP8       (AV_CODEC_ID_VP8 + 10000, AV_CODEC_ID_VP8, "AV_CODEC_ID_VP8", "vp8");
    EyerAVCodecID EyerAVCodecID::CODEC_ID_VP9       (AV_CODEC_ID_VP9 + 10000, AV_CODEC_ID_VP9, "AV_CODEC_ID_VP9", "vp9");

    EyerAVCodecID EyerAVCodecID::CODEC_ID_GIF       (AV_CODEC_ID_GIF + 10000, AV_CODEC_ID_GIF, "AV_CODEC_ID_GIF", "gif");
    EyerAVCodecID EyerAVCodecID::CODEC_ID_MJPEG     (AV_CODEC_ID_MJPEG + 10000, AV_CODEC_ID_MJPEG, "AV_CODEC_ID_MJPEG", "mjpeg");
    EyerAVCodecID EyerAVCodecID::CODEC_ID_PNG       (AV_CODEC_ID_PNG + 10000, AV_CODEC_ID_PNG, "AV_CODEC_ID_PNG", "png");

    EyerAVCodecID EyerAVCodecID::CODEC_ID_AAC       (AV_CODEC_ID_AAC + 10000, AV_CODEC_ID_AAC, "AV_CODEC_ID_AAC", "AAC");
    EyerAVCodecID EyerAVCodecID::CODEC_ID_MP3       (AV_CODEC_ID_MP3 + 10000, AV_CODEC_ID_MP3, "AV_CODEC_ID_MP3", "MP3");
    EyerAVCodecID EyerAVCodecID::CODEC_ID_LIB_OPUS  (AV_CODEC_ID_OPUS + 10000, AV_CODEC_ID_OPUS, "AV_CODEC_ID_OPUS", "opus");

    EyerAVCodecID EyerAVCodecID::CODEC_ID_FLAC      (AV_CODEC_ID_FLAC + 10000, AV_CODEC_ID_FLAC, "AV_CODEC_ID_FLAC", "FLAC");

    EyerAVCodecID EyerAVCodecID::CODEC_ID_PCM_S16LE (AV_CODEC_ID_PCM_S16LE + 10000, AV_CODEC_ID_PCM_S16LE, "CODEC_ID_PCM_S16LE", "PCM_S16LE");
    EyerAVCodecID EyerAVCodecID::CODEC_ID_PCM_S24LE (AV_CODEC_ID_PCM_S24LE + 10000, AV_CODEC_ID_PCM_S24LE, "CODEC_ID_PCM_S24LE", "PCM_S24LE");
    EyerAVCodecID EyerAVCodecID::CODEC_ID_PCM_S32LE (AV_CODEC_ID_PCM_S32LE + 10000, AV_CODEC_ID_PCM_S32LE, "CODEC_ID_PCM_S32LE", "PCM_S32LE");

    EyerAVCodecID EyerAVCodecID::GetCodecIdById(int id)
    {
        if(id == CODEC_ID_H264.GetId()){
            return CODEC_ID_H264;
        }
        else if(id == CODEC_ID_H265.GetId()){
            return CODEC_ID_H265;
        }
        else if(id == CODEC_ID_VP8.GetId()){
            return CODEC_ID_VP8;
        }
        else if(id == CODEC_ID_VP9.GetId()){
            return CODEC_ID_VP9;
        }

        else if(id == CODEC_ID_GIF.GetId()){
            return CODEC_ID_GIF;
        }
        else if(id == CODEC_ID_MJPEG.GetId()){
            return CODEC_ID_MJPEG;
        }
        else if(id == CODEC_ID_PNG.GetId()){
            return CODEC_ID_PNG;
        }

        else if(id == CODEC_ID_AAC.GetId()){
            return CODEC_ID_AAC;
        }
        else if(id == CODEC_ID_MP3.GetId()){
            return CODEC_ID_MP3;
        }
        else if(id == CODEC_ID_LIB_OPUS.GetId()){
            return CODEC_ID_LIB_OPUS;
        }
        else if(id == CODEC_ID_FLAC.GetId()){
            return CODEC_ID_FLAC;
        }

        else if(id == CODEC_ID_PCM_S16LE.GetId()){
            return CODEC_ID_PCM_S16LE;
        }
        else if(id == CODEC_ID_PCM_S24LE.GetId()){
            return CODEC_ID_PCM_S24LE;
        }
        else if(id == CODEC_ID_PCM_S32LE.GetId()){
            return CODEC_ID_PCM_S32LE;
        }

        return CODEC_ID_UNKNOW;
    }

    EyerAVCodecID::EyerAVCodecID()
    {

    }

    EyerAVCodecID::EyerAVCodecID(int _id, int _ffmpegId, const EyerString & _name, const EyerString & _descName)
    {
        id = _id;
        ffmpegId = _ffmpegId;
        name = _name;
        descName = _descName;
    }

    EyerAVCodecID::EyerAVCodecID(const EyerAVCodecID & codecId)
    {
        *this = codecId;
    }

    EyerAVCodecID & EyerAVCodecID::operator = (const EyerAVCodecID & codecId)
    {
        id          = codecId.id;
        ffmpegId    = codecId.ffmpegId;
        name        = codecId.name;
        descName    = codecId.descName;
        return *this;
    }

    bool EyerAVCodecID::operator == (const EyerAVCodecID & format) const
    {
        return id == format.id;
    }

    bool EyerAVCodecID::operator != (const EyerAVCodecID & format) const
    {
        return id != format.id;
    }

    const EyerString EyerAVCodecID::GetDescName() const
    {
        return descName;
    }

    const int EyerAVCodecID::GetId() const
    {
        return id;
    }

    const int EyerAVCodecID::GetFFmpegId() const
    {
        return ffmpegId;
    }

    const EyerString EyerAVCodecID::GetName() const
    {
        return name;
    }
}