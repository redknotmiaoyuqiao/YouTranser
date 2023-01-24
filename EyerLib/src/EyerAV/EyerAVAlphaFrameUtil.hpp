#ifndef EYERLIB_EYERAVALPHAFRAMEUTIL_HPP
#define EYERLIB_EYERAVALPHAFRAMEUTIL_HPP

#include "EyerAVFrame.hpp"

namespace Eyer
{
    class EyerAVAlphaFrameUtil
    {
    public:
        EyerAVAlphaFrameUtil();
        ~EyerAVAlphaFrameUtil();

        EyerAVFrame Convert(EyerAVFrame & frame);
    };
}

#endif //EYERLIB_EYERAVALPHAFRAMEUTIL_HPP
