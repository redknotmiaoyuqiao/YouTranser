#ifndef EYERLIB_EYERAVFRAMEIMAGE_HPP
#define EYERLIB_EYERAVFRAMEIMAGE_HPP

#include <gtest/gtest.h>
#include "EyerAV/EyerAV.hpp"

TEST(EyerAV, EyerAVImageUtilTest)
{
    Eyer::EyerAVDecoderLineParams params;
    Eyer::EyerAVDecoderBoxGroup decoderBoxGroup(params);

    Eyer::EyerAVFrame frame;
    int ret = decoderBoxGroup.GetFrame(frame, "./demo.mp4", 3.0);
    if(!ret){
        EyerLog("w: %d, h: %d\n", frame.GetWidth(), frame.GetHeight());

        Eyer::EyerImageUtil imageUtil;
        imageUtil.WriteFrame(frame, "./image.jpg");
    }
}

#endif //EYERLIB_EYERAVFRAMEIMAGE_HPP
