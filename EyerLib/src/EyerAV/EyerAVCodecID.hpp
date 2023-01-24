#ifndef EYERLIB_EYERAVCODECID_HPP
#define EYERLIB_EYERAVCODECID_HPP

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerAVCodecID
    {
    public:
        static EyerAVCodecID CODEC_ID_UNKNOW;
        static EyerAVCodecID CODEC_ID_H264;

        static EyerAVCodecID CODEC_ID_GIF;
        static EyerAVCodecID CODEC_ID_MP3;
        static EyerAVCodecID CODEC_ID_MJPEG;
        static EyerAVCodecID CODEC_ID_PNG;

        static EyerAVCodecID CODEC_ID_AAC;
        static EyerAVCodecID CODEC_ID_H265;
        static EyerAVCodecID CODEC_ID_VP8;
        static EyerAVCodecID CODEC_ID_VP9;

        static EyerAVCodecID CODEC_ID_LIB_OPUS;
        static EyerAVCodecID CODEC_ID_FLAC;

        static EyerAVCodecID CODEC_ID_PCM_S16LE;

        static EyerAVCodecID GetCodecIdById(int id);

        EyerAVCodecID();
        EyerAVCodecID(int id, int ffmpegId, const EyerString & name, const EyerString & descName);
        EyerAVCodecID(const EyerAVCodecID & codecId);

        EyerAVCodecID & operator = (const EyerAVCodecID & codecId);

        bool operator == (const EyerAVCodecID & format) const;
        bool operator != (const EyerAVCodecID & format) const;

        const int GetId() const;
        const int GetFFmpegId() const;
        const EyerString GetName() const;
        const EyerString GetDescName() const;
    private:
        int id = 0;
        int ffmpegId = 0;
        EyerString name = "";
        EyerString descName = "";
    };
}

#endif //EYERLIB_EYERAVCODECID_HPP
