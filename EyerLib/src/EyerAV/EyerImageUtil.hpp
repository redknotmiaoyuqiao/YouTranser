#ifndef EYERLIB_EYERIMAGEUTIL_HPP
#define EYERLIB_EYERIMAGEUTIL_HPP

#include "EyerAVFrame.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerImageUtil {
    public:
        int WriteFrame(EyerAVFrame & frame, const EyerString & path);
    };
}

#endif //EYERLIB_EYERIMAGEUTIL_HPP
