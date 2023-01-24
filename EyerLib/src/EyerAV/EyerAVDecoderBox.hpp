#ifndef EYERLIB_EYERAVDECODERBOX_HPP
#define EYERLIB_EYERAVDECODERBOX_HPP

#include <vector>

#include "EyerCore/EyerCore.hpp"
#include "EyerAVDecoderLine.hpp"
#include "EyerAVDecoderLineParams.hpp"

namespace Eyer
{
    class EyerAVDecoderBox
    {
    public:
        EyerAVDecoderBox(const EyerString & _path);
        EyerAVDecoderBox(const EyerString & _path, const EyerAVDecoderLineParams & _params);
        ~EyerAVDecoderBox();

        int GetFrame(EyerAVFrame & frame, double pts);

        double GetDuration();

    public:
        EyerString path;
        EyerAVDecoderLineParams params;

        std::vector<EyerAVDecoderLine *> decoderLineCache;

        EyerAVDecoderLine * findDecoderLine(double pts);
    };
}

#endif //EYERLIB_EYERAVDECODERBOX_HPP
