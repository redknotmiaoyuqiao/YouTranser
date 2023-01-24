#ifndef EYERLIB_EYERAVTRANSCODESTREAM_HPP
#define EYERLIB_EYERAVTRANSCODESTREAM_HPP

#include <stdint.h>

#include "EyerAV/EyerAVHeader.hpp"

namespace Eyer
{
    class EyerAVTranscodeStream
    {
    public:
        EyerAVDecoder * decoder = nullptr;
        EyerAVEncoder * encoder = nullptr;
        EyerAVResample * resample = nullptr;
        int writeStreamId = -1;
        int64_t audioPts = 0;
    };
}

#endif //EYERLIB_EYERAVTRANSCODESTREAM_HPP
