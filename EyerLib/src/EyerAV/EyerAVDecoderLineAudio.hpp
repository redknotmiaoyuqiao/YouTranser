#ifndef EYERLIB_EYERAVDECODERLINEAUDIO_HPP
#define EYERLIB_EYERAVDECODERLINEAUDIO_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerAVFrame.hpp"
#include "EyerAVResample.hpp"

namespace Eyer
{
    class EyerAVDecoderLineAudio
    {
    public:
        EyerAVDecoderLineAudio(const EyerString & _path, const EyerString & _cacheFilePath);
        ~EyerAVDecoderLineAudio();

        int GetFrame(EyerAVFrame & distFrame, int offset, int length);

        long long GetSampleCount();
    private:
        int ProgressFrame(EyerAVFrame & avFrame, FILE * cacheFile);

        EyerString path;
        EyerAVResample * resample = nullptr;
        long long sampleCount = 0;

        EyerString cacheFilePath;
    };
}

#endif //EYERLIB_EYERAVDECODERLINEAUDIO_HPP
