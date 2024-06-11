#ifndef EYERLIB_EYERAVDECODERPRIVATE_HPP
#define EYERLIB_EYERAVDECODERPRIVATE_HPP

#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    class EyerAVDecoderPrivate
    {
    public:
        AVCodecContext * codecContext = nullptr;
        AVRational streamTimebase;
        int angle = 0;
    };
}

#endif //EYERLIB_EYERAVDECODERPRIVATE_HPP
