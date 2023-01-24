#ifndef EYERLIB_EYERAVFRAMEPRIVATE_HPP
#define EYERLIB_EYERAVFRAMEPRIVATE_HPP

#include "EyerAVFFmpegHeader.hpp"

#include <vector>
#include <stdint.h>

namespace Eyer
{
    class EyerAVFramePrivate
    {
    public:
        AVFrame * frame = nullptr;
        double secPTS = 0.0;
        bool LAST_FRAME_FLAG = false;
        std::vector<uint8_t *> data;
    };
}

#endif //EYERLIB_EYERAVFRAMEPRIVATE_HPP
