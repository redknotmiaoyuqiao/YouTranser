#ifndef EYERLIB_EYERAVENCODERPRIVATE_HPP
#define EYERLIB_EYERAVENCODERPRIVATE_HPP

#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    class EyerAVEncoderPrivate
    {
    public:
        AVCodecContext * codecContext = nullptr;
    };
}

#endif //EYERLIB_EYERAVENCODERPRIVATE_HPP
