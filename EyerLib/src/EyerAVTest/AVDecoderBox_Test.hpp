#ifndef EYERLIB_AVDECODERBOX_TEST_HPP
#define EYERLIB_AVDECODERBOX_TEST_HPP

#include <gtest/gtest.h>
#include "EyerAV/EyerAV.hpp"

TEST(EyerAV, AVDecoderBox_Test__Sequence_pts)
{
    Eyer::EyerAVDecoderBox decoderBox("./ZhongLi.mp4");
    int index = 0;
    for(double i = 0; i < 90.0; i += (1.0 / 1000.0))
    {
        double pts = i;
        EyerLog("Frame Index: %d, PTS: %f\n", index, pts);

        Eyer::EyerAVFrame frame;
        int ret = decoderBox.GetFrame(frame, pts);

        ASSERT_EQ(ret, 0);

        Eyer::EyerAVPixelFormat pixFormat = frame.GetPixelFormat();
        Eyer::EyerString pixName = pixFormat.GetName();
        EyerLog("Pixel Name: %s\n", pixName.c_str());

        index++;

        double d = abs(frame.GetSecPTS() - pts);
        ASSERT_LE(d, 0.02) << "D too large";
    }
}
/*
TEST(EyerAV, AVDecoderBox_Test__Random_pts)
{
    int frameCount = 1000;
    Eyer::EyerAVDecoderBox decoderBox("./ZhongLi.mp4");
    for(int i = 0; i < frameCount; i++){
        int rand = Eyer::EyerRand::Rand(frameCount);
        double pts = 90.0 / (frameCount) * rand;
        EyerLog("Frame Index: %d, PTS: %f\n", i, pts);

        Eyer::EyerAVFrame frame;
        int ret = decoderBox.GetFrame(frame, pts);

        ASSERT_EQ(ret, 0);

        double d = abs(frame.GetSecPTS() - pts);
        ASSERT_LE(d, 0.02) << "D too large";
    }
}
 */

#endif //EYERLIB_AVDECODERBOX_TEST_HPP
