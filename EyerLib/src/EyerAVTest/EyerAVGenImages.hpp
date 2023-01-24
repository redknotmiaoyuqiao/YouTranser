#ifndef EYERLIB_EYERAVGENIMAGES_HPP
#define EYERLIB_EYERAVGENIMAGES_HPP

#include <gtest/gtest.h>
#include "EyerAV/EyerAV.hpp"

TEST(EyerAV, EyerAVFrameGenImage_1)
{
    int width = 2048;
    int height = 2048;
    Eyer::EyerAVFrame frame;
    frame.SetWidth(width);
    frame.SetHeight(height);
    frame.SetPixelFormat(Eyer::EyerAVPixelFormat::EYER_RGBA);
    frame.GetBuffer();

    uint8_t * data = frame.GetData();
    for(int i=0; i<width * height; i++){
        data[i * 4 + 0] = 234;
        data[i * 4 + 1] = 0;
        data[i * 4 + 2] = 0;
        data[i * 4 + 3] = 255;
    }

    Eyer::EyerAVImageWriter writer;
    writer.WriteFrame(frame, "./image1.png", Eyer::EyerAVPixelFormat::EYER_RGBA);
}

TEST(EyerAV, EyerAVFrameGenImage_2)
{
    int width = 2048;
    int height = 2048;
    Eyer::EyerAVFrame frame;
    frame.SetWidth(width);
    frame.SetHeight(height);
    frame.SetPixelFormat(Eyer::EyerAVPixelFormat::EYER_RGBA);
    frame.GetBuffer();

    uint8_t * data = frame.GetData();
    for(int i=0; i<width * height; i++){
        data[i * 4 + 0] = Eyer::EyerRand::Rand(255);
        data[i * 4 + 1] = Eyer::EyerRand::Rand(255);
        data[i * 4 + 2] = Eyer::EyerRand::Rand(255);
        data[i * 4 + 3] = 255;
    }

    Eyer::EyerAVImageWriter writer;
    writer.WriteFrame(frame, "./image2.png", Eyer::EyerAVPixelFormat::EYER_RGBA);
}

#endif //EYERLIB_EYERAVGENIMAGES_HPP
