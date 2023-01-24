#include "EyerAVMediaType.hpp"

#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    EyerAVMediaType EyerAVMediaType::MEDIA_TYPE_UNKNOWN         (AVMEDIA_TYPE_UNKNOWN, AVMEDIA_TYPE_UNKNOWN, "AVMEDIA_TYPE_UNKNOWN");
    EyerAVMediaType EyerAVMediaType::MEDIA_TYPE_VIDEO           (AVMEDIA_TYPE_VIDEO, AVMEDIA_TYPE_VIDEO, "AVMEDIA_TYPE_VIDEO");
    EyerAVMediaType EyerAVMediaType::MEDIA_TYPE_AUDIO           (AVMEDIA_TYPE_AUDIO, AVMEDIA_TYPE_AUDIO, "AVMEDIA_TYPE_AUDIO");
    EyerAVMediaType EyerAVMediaType::MEDIA_TYPE_DATA            (AVMEDIA_TYPE_DATA, AVMEDIA_TYPE_DATA, "AVMEDIA_TYPE_DATA");
    EyerAVMediaType EyerAVMediaType::MEDIA_TYPE_SUBTITLE        (AVMEDIA_TYPE_SUBTITLE, AVMEDIA_TYPE_SUBTITLE, "AVMEDIA_TYPE_SUBTITLE");
    EyerAVMediaType EyerAVMediaType::MEDIA_TYPE_ATTACHMENT      (AVMEDIA_TYPE_ATTACHMENT, AVMEDIA_TYPE_ATTACHMENT, "AVMEDIA_TYPE_ATTACHMENT");

    EyerAVMediaType EyerAVMediaType::GetMediaTypeByFFmpegId(int ffmpegId)
    {
        if(ffmpegId == AVMediaType::AVMEDIA_TYPE_UNKNOWN){
            return EyerAVMediaType::MEDIA_TYPE_UNKNOWN;
        }
        else if(ffmpegId == AVMediaType::AVMEDIA_TYPE_VIDEO){
            return EyerAVMediaType::MEDIA_TYPE_VIDEO;
        }
        else if(ffmpegId == AVMediaType::AVMEDIA_TYPE_AUDIO){
            return EyerAVMediaType::MEDIA_TYPE_AUDIO;
        }
        else if(ffmpegId == AVMediaType::AVMEDIA_TYPE_SUBTITLE){
            return EyerAVMediaType::MEDIA_TYPE_SUBTITLE;
        }
        else if(ffmpegId == AVMediaType::AVMEDIA_TYPE_ATTACHMENT){
            return EyerAVMediaType::MEDIA_TYPE_ATTACHMENT;
        }
        return EyerAVMediaType::MEDIA_TYPE_UNKNOWN;
    }

    EyerAVMediaType::EyerAVMediaType()
    {
        *this = MEDIA_TYPE_UNKNOWN;
    }

    EyerAVMediaType::EyerAVMediaType(int _id, int _ffmpegId, const EyerString & _name)
    {
        id          = _id;
        ffmpegId    = _ffmpegId;
        name        = _name;
    }

    EyerAVMediaType::EyerAVMediaType(const EyerAVMediaType & type)
    {
        *this = type;
    }

    const EyerAVMediaType & EyerAVMediaType::operator = (const EyerAVMediaType & type)
    {
        id          = type.id;
        ffmpegId    = type.ffmpegId;
        name        = type.name;
        return *this;
    }

    bool EyerAVMediaType::operator == (const EyerAVMediaType & type) const
    {
        return id == type.id;
    }

    bool EyerAVMediaType::operator != (const EyerAVMediaType & type) const
    {
        return id != type.id;
    }

    int EyerAVMediaType::GetId() const
    {
        return id;
    }

    int EyerAVMediaType::GetFFmpegId() const
    {
        return ffmpegId;
    }

    EyerString EyerAVMediaType::GetName() const
    {
        return name;
    }
}