#ifndef EYERLIB_EYERAVSEIUTIL_HPP
#define EYERLIB_EYERAVSEIUTIL_HPP

#include <stdint.h>
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerAVSEIUtil
    {
    public:
        EyerAVSEIUtil();
        ~EyerAVSEIUtil();

        EyerBufferPlus GenSEINALU(uint8_t * msg, int msgLen);
    };
}

#endif //EYERLIB_EYERAVSEIUTIL_HPP
