#ifndef EYERLIB_EYERAVIMAGEWRITER_HPP
#define EYERLIB_EYERAVIMAGEWRITER_HPP

#include "EyerAVFrame.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerAVImageWriter
    {
    public:
        EyerAVImageWriter();
        ~EyerAVImageWriter();

        int WriteFrame(EyerAVFrame & frame, const EyerString & path, const EyerAVPixelFormat & pixelFormat);
    };
}

#endif //EYERLIB_EYERAVIMAGEWRITER_HPP
