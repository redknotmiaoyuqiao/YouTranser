#ifndef EYERLIB_EYERAVREADERPRIVATE_HPP
#define EYERLIB_EYERAVREADERPRIVATE_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    class EyerAVReaderPrivate
    {
    public:
        EyerString path;

        AVFormatContext * formatCtx = nullptr;
    };
}

#endif //EYERLIB_EYERAVREADERPRIVATE_HPP
