#ifndef EYERLIB_EYERAVSTREAMPRIVATE_HPP
#define EYERLIB_EYERAVSTREAMPRIVATE_HPP

#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    class EyerAVStreamPrivate
    {
    public:
        AVCodecParameters * codecpar = nullptr;
        // AVCodecContext * codec = nullptr;
        AVRational timebase;
        int stream_id = 0;
        double duration = 0.0;
        int angle = 0;
    };
}

#endif //EYERLIB_EYERAVSTREAMPRIVATE_HPP
