#ifndef EYERLIB_EYERAVDECODERLINE_HPP
#define EYERLIB_EYERAVDECODERLINE_HPP

#include <vector>

#include "EyerCore/EyerCore.hpp"

#include "EyerAVFrame.hpp"
#include "EyerAVDecoder.hpp"
#include "EyerAVReader.hpp"
#include "EyerAVDecoderLineParams.hpp"

namespace Eyer
{
    class EyerAVDecoderLine {
    public:
        EyerAVDecoderLine(const EyerString & _path, double _startSeekTime);
        EyerAVDecoderLine(const EyerString & _path, double _startSeekTime, const EyerAVDecoderLineParams & _params);
        ~EyerAVDecoderLine();

        int GetFrame(EyerAVFrame & frame, double pts);

        int GetCacheSize();

        double GetStartTime();

    public:
        EyerAVReader * reader = nullptr;
        EyerAVDecoder * decoder = nullptr;

        std::vector<EyerAVFrame *> frameCache;

        double startSeekTime = 0.0;

        int currentStreamIndex = -1;
        bool isEOF = false;

        int SearchFrameInCache(EyerAVFrame & frame, double pts);

        int DecodeFrame();
        int ClearCache(int maxDropFrames);

        EyerAVDecoderLineParams params;

        EyerAVFrame * lastFrame = nullptr;
        int PutFrame(EyerAVFrame * _lastFrame);
    };
}

#endif //EYERLIB_EYERAVDECODERLINETEST_HPP
