#ifndef EYERLIB_EYERAVIMAGEREADERTEST_HPP
#define EYERLIB_EYERAVIMAGEREADERTEST_HPP

#include <gtest/gtest.h>
#include "EyerAV/EyerAV.hpp"

TEST(EyerAV, EyerAVImageReaderTest)
{
    for(int i=0; i<1000; i++){
        Eyer::EyerAVImageReader imageReader;

        Eyer::EyerAVFrame frame;
        int ret = imageReader.ReadFrame(frame, "./2.jpg");
        ASSERT_EQ(ret, 0) << "ReadFrame Error";

        ASSERT_EQ(frame.GetWidth(), 1080) << "ReadFrame Error";
        ASSERT_EQ(frame.GetHeight(), 1080) << "ReadFrame Error";

        // EyerLog("width: %d, height: %d\n", frame.GetWidth(), frame.GetHeight());
    }

    for(int i=0; i<1000; i++){
        Eyer::EyerAVImageReader imageReader;

        Eyer::EyerAVFrame frame;
        int ret = imageReader.ReadFrame(frame, "./1.png");
        ASSERT_EQ(ret, 0) << "ReadFrame Error";

        ASSERT_EQ(frame.GetWidth(), 108) << "ReadFrame Error";
        ASSERT_EQ(frame.GetHeight(), 112) << "ReadFrame Error";

        // EyerLog("width: %d, height: %d\n", frame.GetWidth(), frame.GetHeight());
    }

    for(int i=0; i<1000; i++){
        Eyer::EyerAVImageReader imageReader;

        Eyer::EyerAVFrame frame;
        int ret = imageReader.ReadFrame(frame, "./3.png");
        ASSERT_EQ(ret, 0) << "ReadFrame Error";

        ASSERT_EQ(frame.GetWidth(), 706) << "ReadFrame Error";
        ASSERT_EQ(frame.GetHeight(), 476) << "ReadFrame Error";

        Eyer::EyerAVFrame destframe;
        frame.Scale(destframe, Eyer::EyerAVPixelFormat::EYER_YUYV422, 120, 800);
        ASSERT_EQ(destframe.GetWidth(), 120) << "ReadFrame Error";
        ASSERT_EQ(destframe.GetHeight(), 800) << "ReadFrame Error";

        // EyerLog("width: %d, height: %d\n", frame.GetWidth(), frame.GetHeight());
    }
}

#endif //EYERLIB_EYERAVIMAGEREADERTEST_HPP
