#ifndef EYERLIB_EYERAVMEDIAINFOTEST_HPP
#define EYERLIB_EYERAVMEDIAINFOTEST_HPP

#include <gtest/gtest.h>
#include "EyerAV/EyerAV.hpp"

TEST(EyerAV, EyerAVMediaInfoTest)
{
    Eyer::EyerMediaInfoParse mediaInfoParse;
    int ret = mediaInfoParse.Parse("./demo.mp4");
    if(ret == 0){
        Eyer::EyerMediaInfo mediaInfo = mediaInfoParse.GetInfo();
        int streamSize = mediaInfo.GetStreamSize();
        EyerLog("Stream Size: %d\n", streamSize);

        for(int i=0;i<streamSize;i++){
            Eyer::EyerAVStream stream = mediaInfo.GetStream(i);
            EyerLog("\tstream ID:%d\n", stream.GetType().GetFFmpegId());
            if(stream.GetType() == Eyer::EyerAVMediaType::MEDIA_TYPE_VIDEO){
                stream.GetCodecID();
                int width = stream.GetWidth();
                int height = stream.GetHeight();
                EyerLog("\t\tWidth: %d, height: %d\n", width, height);
            }
            else if(stream.GetType() == Eyer::EyerAVMediaType::MEDIA_TYPE_AUDIO){

            }
        }
    }
}

#endif //EYERLIB_EYERAVMEDIAINFOTEST_HPP
