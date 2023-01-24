#ifndef EYERLIB_EYERAVRESAMPLEPRIVATE_HPP
#define EYERLIB_EYERAVRESAMPLEPRIVATE_HPP

#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    class EyerAVResamplePrivate
    {
    public:
        SwrContext * swrCtx = nullptr;

        EyerAVChannelLayout outputChannelLayout;
        EyerAVChannelLayout inputChannelLayout;
        EyerAVSampleFormat outputSampleFormat;
        EyerAVSampleFormat inputSampleFormat;
        int outputSamplerate;
        int inputSamplerate;

        AVAudioFifo * inputFifo = nullptr;
        AVAudioFifo * outputFifo = nullptr;

        int inputBlockSize = 0;
        int outputBlockSize = 0;

    };
}

#endif //EYERLIB_EYERAVRESAMPLEPRIVATE_HPP
