#ifndef EYERLIB_EYERAVAUDIOFIFO_HPP
#define EYERLIB_EYERAVAUDIOFIFO_HPP

#include "EyerAVFrame.hpp"
#include "EyerAVSampleFormat.hpp"

namespace Eyer
{
    class EyerAVAudioFifoPrivate;

    class EyerAVAudioFifo
    {
    public:
        EyerAVAudioFifo(EyerAVSampleFormat sampleFormat, EyerAVChannelLayout channelLayout, int sampleRate);
        ~EyerAVAudioFifo();

        int PutAVFrame(EyerAVFrame & avFrame);
        int GetAVFrame(EyerAVFrame & avFrame, int sampleNB);

    private:
        EyerAVAudioFifoPrivate * piml = nullptr;
    };
}

#endif //EYERLIB_EYERAVAUDIOFIFO_HPP
