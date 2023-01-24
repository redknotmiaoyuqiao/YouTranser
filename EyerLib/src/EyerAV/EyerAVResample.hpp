#ifndef EYERLIB_EYERAVRESAMPLE_HPP
#define EYERLIB_EYERAVRESAMPLE_HPP

#include "EyerAVFrame.hpp"
#include "EyerAVChannelLayout.hpp"
#include "EyerAVSampleFormat.hpp"

namespace Eyer
{
    class EyerAVResamplePrivate;
    class EyerAVResample
    {
    public:
        EyerAVResample();
        ~EyerAVResample();

        int Init(
                EyerAVChannelLayout     outputChannelLayout,
                EyerAVSampleFormat      outputSampleFormat,
                int                     outputSamplerate,

                EyerAVChannelLayout     inputChannelLayout,
                EyerAVSampleFormat      inputSampleFormat,
                int                     inputSamplerate
                );

        int PutAVFrame(EyerAVFrame & frame);
        int PutAVFrameNULL();
        int GetFrame(EyerAVFrame & frame, int frameSize);
        int GetLastFrame(EyerAVFrame & frame, int frameSize);

        EyerAVResamplePrivate * piml = nullptr;
    };
}

#endif //EYERLIB_EYERAVRESAMPLE_HPP
