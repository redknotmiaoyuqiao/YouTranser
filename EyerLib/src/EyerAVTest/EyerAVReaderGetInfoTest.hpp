#ifndef EYERLIB_EYERAVREADERGETINFOTEST_HPP
#define EYERLIB_EYERAVREADERGETINFOTEST_HPP

#include <gtest/gtest.h>
#include "EyerAV/EyerAV.hpp"

TEST(EyerAV, EyerAVReaderGetInfoTest)
{
    Eyer::EyerAVReader reader("./demo.mp4");

    reader.Open();

    while(1){
        Eyer::EyerAVPacket packet;
        int ret = reader.Read(packet);
        if(ret){
            break;
        }
    }

    reader.Close();
}

#endif //EYERLIB_EYERAVREADERGETINFOTEST_HPP
