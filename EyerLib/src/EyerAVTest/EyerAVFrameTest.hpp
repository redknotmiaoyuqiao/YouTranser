#ifndef EYERLIB_EYERAVFRAMETEST_HPP
#define EYERLIB_EYERAVFRAMETEST_HPP

#include <gtest/gtest.h>
#include "EyerAV/EyerAV.hpp"

TEST(EyerAV, EyerAVFrameTest)
{
    for(int i=0; i<1000; i++){
        Eyer::EyerAVFrame * frame = new Eyer::EyerAVFrame();
        delete frame;
    }
}

#endif //EYERLIB_EYERAVFRAMETEST_HPP
