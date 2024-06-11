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
        EyerAVDecoderBox(const EyerString & _path, EyerAVReaderCustomIO * _customIO = nullptr);
        EyerAVDecoderBox(const EyerString & _path, const EyerAVDecoderLineParams & _params, EyerAVReaderCustomIO * _customIO = nullptr);
        ~EyerAVDecoderBox();

        int GetFrame(EyerAVFrame & frame, double pts);
        int GetFrameInternal(EyerAVFrame & frame, double pts);

        double GetDuration();

    public:
        EyerString path;
        EyerAVDecoderLineParams params;

        std::vector<EyerAVDecoderLine *> decoderLineCache;

        EyerAVDecoderLine * findDecoderLine(double pts);

        EyerAVReaderCustomIO * customIO = nullptr;
    };
}

#endif //EYERLIB_EYERAVDECODERBOX_HPP
