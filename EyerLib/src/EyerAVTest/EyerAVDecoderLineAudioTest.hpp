#ifndef EYERLIB_EYERAVDECODERLINETEST_HPP
#define EYERLIB_EYERAVDECODERLINETEST_HPP

#include "EyerAV/EyerAV.hpp"
#include <math.h>

TEST(EyerAV, EyerAVDecoderLineAudioTest)
{
    // Eyer::EyerAVDecoderLineAudio decoderLineAudio("/Users/miaoyuqiao/VVV/ysjf_.mp4", "/Users/miaoyuqiao/VVV/ysjf.pcm");
    Eyer::EyerAVDecoderLineAudio decoderLineAudio("./test_image.png", "/Users/miaoyuqiao/VVV/ysjf.pcm");

    Eyer::EyerAVFrame frame;
    int ret = decoderLineAudio.GetFrame(frame, 44100 * 10, 1024);

    EyerLog("Ret: %d\n", ret);
}

#endif //EYERLIB_EYERAVDECODERLINETEST_HPP
