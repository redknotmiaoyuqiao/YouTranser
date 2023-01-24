#ifndef EYERLIB_EYERAVBITSTREAMFILTERPRIVATE_HPP
#define EYERLIB_EYERAVBITSTREAMFILTERPRIVATE_HPP

#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    class EyerAVBitstreamFilterPrivate
    {
    public:
        AVBSFContext * ctx = nullptr;
    };
}

#endif //EYERLIB_EYERAVBITSTREAMFILTERPRIVATE_HPP
