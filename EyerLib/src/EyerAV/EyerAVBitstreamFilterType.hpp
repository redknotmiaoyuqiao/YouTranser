#ifndef EYERLIB_EYERAVBITSTREAMFILTERTYPE_HPP
#define EYERLIB_EYERAVBITSTREAMFILTERTYPE_HPP

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerAVBitstreamFilterType {
    public:
        static EyerAVBitstreamFilterType H264_MP4TOANNEXB;
        static EyerAVBitstreamFilterType H264_METADATA;
        static EyerAVBitstreamFilterType HEVC_MP4TOANNEXB;

        EyerAVBitstreamFilterType(const EyerString & _str, int _id);
        EyerAVBitstreamFilterType(const EyerAVBitstreamFilterType & type);
        ~EyerAVBitstreamFilterType();

        EyerAVBitstreamFilterType & operator = (const EyerAVBitstreamFilterType & type);

        bool operator == (const EyerAVBitstreamFilterType & type);
        bool operator != (const EyerAVBitstreamFilterType & type);

    public:
        EyerString str;
        int id;
    };
}

#endif //EYERLIB_EYERAVBITSTREAMFILTERTYPE_HPP
