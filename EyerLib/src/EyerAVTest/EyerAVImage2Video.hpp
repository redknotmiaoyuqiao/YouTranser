#ifndef EYERLIB_EYERAVIMAGE2VIDEO_HPP
#define EYERLIB_EYERAVIMAGE2VIDEO_HPP

#include <gtest/gtest.h>
#include "EyerAV/EyerAV.hpp"
#include "EyerCore/EyerCore.hpp"

TEST(EyerAV, EyerAVImage2VideoTestAAA)
{
    uint8_t data[] = {
            255, 0, 0, 255,      0, 255, 0, 255,
            0, 0, 255, 255,      255, 255, 255, 255,
    };

    uint8_t data_[] = {
            255, 0, 0,      0, 255, 0,
            0, 0, 255,      255, 255, 255,
    };

    Eyer::EyerAVImageWriter writer;

    Eyer::EyerAVFrame frame;
    frame.SetWidth(2);
    frame.SetHeight(2);
    frame.SetPixelFormat(Eyer::EyerAVPixelFormat::EYER_RGB24);
    frame.GetBuffer(1);

    uint8_t * d = frame.GetData();
    memcpy(d, data_, 4 * 3);

    writer.WriteFrame(frame, "./test.png", Eyer::EyerAVPixelFormat::EYER_RGB24);
}


TEST(EyerAV, EyerAVImage2VideoTest)
{

}

#endif //EYERLIB_EYERAVIMAGE2VIDEO_HPP
