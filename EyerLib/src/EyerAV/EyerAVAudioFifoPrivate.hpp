#ifndef EYERLIB_EYERAVAUDIOFIFOPRIVATE_HPP
#define EYERLIB_EYERAVAUDIOFIFOPRIVATE_HPP

#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    class EyerAVAudioFifoPrivate
    {
    public:
        AVAudioFifo * fifo = nullptr;

        EyerAVSampleFormat sampleFormat;
        EyerAVChannelLayout channelLayout;
        int sampleRate;
    };
}

#endif //EYERLIB_EYERAVAUDIOFIFOPRIVATE_HPP
