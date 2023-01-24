#ifndef EYERLIB_EYERAVDECODERLINEPARAMS_HPP
#define EYERLIB_EYERAVDECODERLINEPARAMS_HPP

#include "EyerAVPixelFormat.hpp"

namespace Eyer
{
    class EyerAVDecoderLineParams {
    public:
        EyerAVDecoderLineParams();
        EyerAVDecoderLineParams(int _lineCacheMaxFrame);
        ~EyerAVDecoderLineParams();

        int SetScale(const EyerAVPixelFormat & _pixelFormat, int scaleWidth, int scaleHeight);

        int lineCacheMaxFrame       = 5;
        bool isScale                = false;
        EyerAVPixelFormat pixelFormat;
        int scaleWidth              = 0;
        int scaleHeight             = 0;
    };
}

#endif //EYERLIB_EYERAVDECODERLINEPARAMS_HPP
