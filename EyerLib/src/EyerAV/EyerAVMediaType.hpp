#ifndef EYERLIB_EYERAVMEDIATYPE_HPP
#define EYERLIB_EYERAVMEDIATYPE_HPP

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerAVMediaType
    {
    public:
        static EyerAVMediaType MEDIA_TYPE_UNKNOWN;
        static EyerAVMediaType MEDIA_TYPE_VIDEO;
        static EyerAVMediaType MEDIA_TYPE_AUDIO;
        static EyerAVMediaType MEDIA_TYPE_DATA;
        static EyerAVMediaType MEDIA_TYPE_SUBTITLE;
        static EyerAVMediaType MEDIA_TYPE_ATTACHMENT;

        static EyerAVMediaType GetMediaTypeByFFmpegId(int ffmpegId);

        EyerAVMediaType();
        EyerAVMediaType(int id, int ffmpegId, const EyerString & name);
        EyerAVMediaType(const EyerAVMediaType & type);

        const EyerAVMediaType & operator = (const EyerAVMediaType & type);

        bool operator == (const EyerAVMediaType & type) const;
        bool operator != (const EyerAVMediaType & type) const;

        int GetId() const;
        int GetFFmpegId() const;
        EyerString GetName() const;

    private:
        int id = 0;
        int ffmpegId = 0;
        EyerString name = "";
    };

    typedef EyerAVMediaType EyerAVStreamType;
}

#endif //EYERLIB_EYERAVMEDIATYPE_HPP
