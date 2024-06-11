#ifndef SRC_EYERAVAUDIOBOX_HPP
#define SRC_EYERAVAUDIOBOX_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerAVReader.hpp"
#include "EyerAVFrame.hpp"
#include "EyerAVDecoder.hpp"
#include "EyerAVResample.hpp"

namespace Eyer
{
    class EyerAVAudioBox
    {
    public:
        EyerAVAudioBox(const EyerString & _path,
                       EyerAVReaderCustomIO * _customIO,
                       int64_t sampleOffset,
                       EyerAVChannelLayout channelLayout,
                       EyerAVSampleFormat sampleFormat,
                       int samplerate);
        ~EyerAVAudioBox();

        int GetFrame(EyerAVFrame & frame, int wanLen, bool * isEnd = nullptr);

    private:
        EyerString path;
        EyerAVReader * reader = nullptr;
        int audioIndex = -1;
        EyerAVDecoder * decoder = nullptr;
        EyerAVResample * resample = nullptr;

        int64_t sampleOffset;
        EyerAVChannelLayout channelLayout;
        EyerAVSampleFormat sampleFormat;
        int samplerate;
    };
}

#endif //SRC_EYERAVAUDIOBOX_HPP
