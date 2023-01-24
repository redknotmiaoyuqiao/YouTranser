#include "EyerAVTranscodeParams.hpp"

namespace Eyer
{
    EyerAVTranscodeParams::EyerAVTranscodeParams()
    {

    }

    EyerAVTranscodeParams::EyerAVTranscodeParams(const EyerAVTranscodeParams & params)
    {
        *this = params;
    }

    EyerAVTranscodeParams & EyerAVTranscodeParams::operator = (const EyerAVTranscodeParams & params)
    {
        targetWidth     = params.targetWidth;
        targetHeight    = params.targetHeight;
        fps             = params.fps;
        careVideo       = params.careVideo;
        careAudio       = params.careAudio;
        return *this;
    }
}