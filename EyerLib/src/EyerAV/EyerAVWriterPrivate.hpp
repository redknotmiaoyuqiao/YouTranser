#ifndef EYERLIB_EYERAVWRITERPRIVATE_HPP
#define EYERLIB_EYERAVWRITERPRIVATE_HPP

#include "EyerAVFFmpegHeader.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerAVWriterPrivate
    {
    public:
        AVFormatContext * formatCtx = nullptr;
        EyerString path;
    };
}

#endif //EYERLIB_EYERAVWRITERPRIVATE_HPP
