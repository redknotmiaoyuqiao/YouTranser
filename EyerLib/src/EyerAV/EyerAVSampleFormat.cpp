#include "EyerAVSampleFormat.hpp"

#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    EyerAVSampleFormat EyerAVSampleFormat::UNKNOW           (-1, -1, "UNKNOW");
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_U8    (AV_SAMPLE_FMT_U8, AV_SAMPLE_FMT_U8, "AV_SAMPLE_FMT_U8");
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_S16   (AV_SAMPLE_FMT_S16, AV_SAMPLE_FMT_S16, "AV_SAMPLE_FMT_S16");
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_S32   (AV_SAMPLE_FMT_S32, AV_SAMPLE_FMT_S32, "AV_SAMPLE_FMT_S32");
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_FLT   (AV_SAMPLE_FMT_FLT, AV_SAMPLE_FMT_FLT, "AV_SAMPLE_FMT_FLT");
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_DBL   (AV_SAMPLE_FMT_DBL, AV_SAMPLE_FMT_DBL, "AV_SAMPLE_FMT_DBL");

    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_U8P   (AV_SAMPLE_FMT_U8P, AV_SAMPLE_FMT_U8P, "AV_SAMPLE_FMT_U8P");
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_S16P  (AV_SAMPLE_FMT_S16P, AV_SAMPLE_FMT_S16P, "AV_SAMPLE_FMT_S16P");
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_S32P  (AV_SAMPLE_FMT_S32P, AV_SAMPLE_FMT_S32P, "AV_SAMPLE_FMT_S32P");
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_FLTP  (AV_SAMPLE_FMT_FLTP, AV_SAMPLE_FMT_FLTP, "AV_SAMPLE_FMT_FLTP");
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_DBLP  (AV_SAMPLE_FMT_DBLP, AV_SAMPLE_FMT_DBLP, "AV_SAMPLE_FMT_DBLP");


    EyerAVSampleFormat EyerAVSampleFormat::GetByFFmpegId(int ffmpegId)
    {
        if(ffmpegId == AV_SAMPLE_FMT_U8){
            return SAMPLE_FMT_U8;
        }
        if(ffmpegId == AV_SAMPLE_FMT_S16){
            return SAMPLE_FMT_S16;
        }
        if(ffmpegId == AV_SAMPLE_FMT_S32){
            return SAMPLE_FMT_S32;
        }
        if(ffmpegId == AV_SAMPLE_FMT_FLT){
            return SAMPLE_FMT_FLT;
        }
        if(ffmpegId == AV_SAMPLE_FMT_DBL){
            return SAMPLE_FMT_DBL;
        }


        if(ffmpegId == AV_SAMPLE_FMT_U8P){
            return SAMPLE_FMT_U8P;
        }
        if(ffmpegId == AV_SAMPLE_FMT_S16P){
            return SAMPLE_FMT_S16P;
        }
        if(ffmpegId == AV_SAMPLE_FMT_S32P){
            return SAMPLE_FMT_S32P;
        }
        if(ffmpegId == AV_SAMPLE_FMT_FLTP){
            return SAMPLE_FMT_FLTP;
        }
        if(ffmpegId == AV_SAMPLE_FMT_DBLP){
            return SAMPLE_FMT_DBLP;
        }
        return UNKNOW;
    }

    EyerAVSampleFormat::EyerAVSampleFormat()
    {

    }

    EyerAVSampleFormat::EyerAVSampleFormat(int _id, int _ffmpegId, const EyerString & _name)
    {
        id = _id;
        ffmpegId = _ffmpegId;
        name = _name;
    }

    EyerAVSampleFormat::EyerAVSampleFormat(const EyerAVSampleFormat & sampleFormat)
    {
        *this = sampleFormat;
    }

    EyerAVSampleFormat & EyerAVSampleFormat::operator = (const EyerAVSampleFormat & sampleFormat)
    {
        id = sampleFormat.id;
        ffmpegId = sampleFormat.ffmpegId;
        name = sampleFormat.name;
        return *this;
    }

    bool EyerAVSampleFormat::operator == (const EyerAVSampleFormat & format)
    {
        return id == format.id;
    }

    const EyerString EyerAVSampleFormat::GetName() const
    {
        return name;
    }
}