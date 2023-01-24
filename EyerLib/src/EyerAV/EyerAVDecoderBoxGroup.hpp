#ifndef EYERLIB_EYERAVDECODERBOXGROUP_HPP
#define EYERLIB_EYERAVDECODERBOXGROUP_HPP

#include <map>
#include <vector>

#include "EyerCore/EyerCore.hpp"
#include "EyerAVFrame.hpp"
#include "EyerAVDecoderLineParams.hpp"

namespace Eyer
{
    class EyerAVDecoderBox;

    class EyerAVDecoderBoxGroup
    {
    public:
        EyerAVDecoderBoxGroup(const EyerAVDecoderLineParams & _params);
        ~EyerAVDecoderBoxGroup();

        int GetFrame(EyerAVFrame & frame, const EyerString & path, double pts);

    private:
        EyerAVDecoderLineParams params;
        std::map<EyerString, EyerAVDecoderBox *> decoderBoxCache;
        EyerAVDecoderBox * FindDecoderBox(const EyerString & path);
    };
}

#endif //EYERLIB_EYERAVDECODERBOXGROUP_HPP
