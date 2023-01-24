#ifndef EYERLIB_EYERAVDECODERLINETEST_HPP
#define EYERLIB_EYERAVDECODERLINETEST_HPP

#include "EyerAV/EyerAV.hpp"
#include <math.h>


TEST(EyerAV, EyerAVDecoderLineTest)
{
    Eyer::EyerAVDecoderLine decoderLine("./demo.mp4", 0);

    for(double i=0;i<10.0;i+=0.1){
        Eyer::EyerAVFrame frame;
        int ret = decoderLine.GetFrame(frame, i);
        if(ret){
            continue;
        }

        EyerLog("i: %f, Frame PTS: %f, D: %f\n", i, frame.GetSecPTS(), abs(frame.GetSecPTS() - i));

        int cacheSize = decoderLine.GetCacheSize();
        // ASSERT_LE(cacheSize, 10) << "Cache Error";
    }
}

TEST(EyerAV, EyerAVDecoderLineRandomTest)
{
    // Eyer::EyerAVDecoderLine decoderLine("./demo.mp4", 0);

    Eyer::EyerAVDecoderLine * decoderLine = nullptr;

    int countTimes = 20;
    int hitTimes = 0;
    for(int i=0;i<countTimes;i++){
        int rand = Eyer::EyerRand::Rand(10 * 1000);
        double pts = rand * 1.0 / 1000;
        // EyerLog("pts: %f\n", pts);

        if(decoderLine == nullptr){
            decoderLine = new Eyer::EyerAVDecoderLine("./demo.mp4", pts);
        }

        Eyer::EyerAVFrame frame;
        int ret = decoderLine->GetFrame(frame, pts);
        if(ret){
            continue;
        }

        // EyerLog("pts: %f, Frame PTS: %f, D: %f\n", pts, frame.GetSecPTS(), abs(frame.GetSecPTS() - pts));
        if(abs(frame.GetSecPTS() - pts) >= 0.1){
            continue;
        }
        hitTimes++;
    }

    EyerLog("Hit: %f\n", (hitTimes * 1.0) / countTimes);

    if(decoderLine != nullptr){
        delete decoderLine;
        decoderLine = nullptr;
    }
}

TEST(EyerAV, EyerAVDecoderBoxTest_Sequence)
{
    Eyer::EyerAVDecoderBox decoderBox("./demo.mp4");

    double duration = decoderBox.GetDuration();

    int countTimes = 1000;
    for(int i=0;i<countTimes;i++) {
        double step = 1000 * 10.0 / countTimes;
        double pts = i * step;

        // EyerLog("index: %d, Pts: %f\n", i, pts);

        Eyer::EyerAVFrame frame;
        int ret = decoderBox.GetFrame(frame, pts);
        if(ret){
            // EyerLog("GetFrame pts: %f Error, ret: %d\n", pts, ret);
            ASSERT_GE(pts, duration) << "GetFrame Error";
            continue;
        }
        if(pts > duration){
            continue;
        }

        double d = abs(frame.GetSecPTS() - pts);
        ASSERT_LE(d, 0.02) << "D too large";
    }
}

#endif //EYERLIB_EYERAVDECODERLINETEST_HPP
