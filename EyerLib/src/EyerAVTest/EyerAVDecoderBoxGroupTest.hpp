#ifndef EYERLIB_EYERAVDECODERBOXGROUPTEST_HPP
#define EYERLIB_EYERAVDECODERBOXGROUPTEST_HPP

#include <gtest/gtest.h>
#include "EyerAV/EyerAV.hpp"

TEST(EyerAV, EyerAVDecoderBoxGroupTest)
{
    int width = 128;
    int height = 128;


    for(int j=0;j<1;j++){
        for(int i=0;i<10;i++){
            Eyer::EyerAVDecoderLineParams params;
            Eyer::EyerAVDecoderBoxGroup decoderBoxGroup(params);

            Eyer::EyerString path = Eyer::EyerString("./") + Eyer::EyerString::Number(j) + "-" + Eyer::EyerString::Number(i) + ".jpg";
            Eyer::EyerAVFrame frame;
            double pts = i * 1.0;
            if(i % 2){
                int ret = decoderBoxGroup.GetFrame(frame, "./ZhongLi.mp4", pts);
                ASSERT_EQ(ret, 0);

                Eyer::EyerImageUtil imageUtil;
                imageUtil.WriteFrame(frame, path.c_str());
            }
            else {
                int ret = decoderBoxGroup.GetFrame(frame, "./ZhongLi.mp4", pts);
                ASSERT_EQ(ret, 0);

                Eyer::EyerImageUtil imageUtil;
                imageUtil.WriteFrame(frame, path.c_str());
            }

            double d = abs(frame.GetSecPTS() - pts);
            // EyerLog("D: %f\n", d);
            // ASSERT_LE(d, 0.02);

            // ASSERT_EQ(frame.GetWidth(), width);
            // ASSERT_EQ(frame.GetHeight(), height);
        }
    }
}

#endif //EYERLIB_EYERAVDECODERBOXGROUPTEST_HPP
