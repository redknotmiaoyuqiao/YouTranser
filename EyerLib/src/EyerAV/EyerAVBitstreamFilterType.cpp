#include "EyerAVBitstreamFilterType.hpp"

namespace Eyer
{
    EyerAVBitstreamFilterType EyerAVBitstreamFilterType::H264_MP4TOANNEXB   ("h264_mp4toannexb", 1);
    EyerAVBitstreamFilterType EyerAVBitstreamFilterType::HEVC_MP4TOANNEXB   ("hevc_mp4toannexb", 2);
    EyerAVBitstreamFilterType EyerAVBitstreamFilterType::H264_METADATA      ("h264_metadata", 3);

    EyerAVBitstreamFilterType::EyerAVBitstreamFilterType(const EyerString & _str, int _id)
    {
        str = _str;
        id = _id;
    }

    EyerAVBitstreamFilterType::EyerAVBitstreamFilterType(const EyerAVBitstreamFilterType & type)
    {
        *this = type;
    }

    EyerAVBitstreamFilterType::~EyerAVBitstreamFilterType()
    {

    }

    EyerAVBitstreamFilterType & EyerAVBitstreamFilterType::operator = (const EyerAVBitstreamFilterType & type)
    {
        id = type.id;
        str = type.str;

        return *this;
    }

    bool EyerAVBitstreamFilterType::operator == (const EyerAVBitstreamFilterType & type)
    {
        return id == type.id;
    }

    bool EyerAVBitstreamFilterType::operator != (const EyerAVBitstreamFilterType & type)
    {
        return id != type.id;
    }
}