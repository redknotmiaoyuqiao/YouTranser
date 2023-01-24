#ifndef EYERLIB_EYERBUFFERPLUSCALLBACK_HPP
#define EYERLIB_EYERBUFFERPLUSCALLBACK_HPP

#include <stdint.h>

#include "EyerBuffer.hpp"

namespace Eyer
{
    class EyerBufferPlusCallback {
    public:
        virtual int ReadBuffer(uint8_t * buf, int needLen) = 0;
        virtual uint64_t GetLen() = 0;

        virtual int WriteBuffer(EyerBuffer & buffer) = 0;
    };
}

#endif //EYERLIB_EYERBUFFERPLUSCALLBACK_HPP
