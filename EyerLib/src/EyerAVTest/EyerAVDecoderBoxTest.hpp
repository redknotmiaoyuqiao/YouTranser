#ifndef EYERLIB_EYERAVDECODERBOXTEST_HPP
#define EYERLIB_EYERAVDECODERBOXTEST_HPP

#include <gtest/gtest.h>
#include "EyerAV/EyerAV.hpp"

TEST(EyerAV, EyerAVDecoderBoxTest)
{
    Eyer::EyerAVDecoderBox decoderBox("./2.jpg");

    double duration = decoderBox.GetDuration();

    int countTimes = 1000;
    for(int i=0;i<countTimes;i++) {
        int rand = Eyer::EyerRand::Rand(10 * 1000);
        double pts = rand * 1.0 / 1000 + 10.0;

        // EyerLog("index: %d, Pts: %f\n", i, pts);

        Eyer::EyerAVFrame frame;
        int ret = decoderBox.GetFrame(frame, pts);
        EyerLog("ret: %d\n", ret);
        EyerLog("width: %d, height: %d\n", frame.GetWidth(), frame.GetHeight());
    }
}

#endif //EYERLIB_EYERAVDECODERBOXTEST_HPP
