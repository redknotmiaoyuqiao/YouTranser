#ifndef EYERLIB_EYERAVPACKETTEST_HPP
#define EYERLIB_EYERAVPACKETTEST_HPP

#include <gtest/gtest.h>
#include "EyerAV/EyerAV.hpp"

TEST(EyerAV, EyerAVPacketTest)
{
    for(int i=0; i<1000; i++){
        Eyer::EyerAVPacket * packet = new Eyer::EyerAVPacket();
        delete packet;
    }
}

#endif //EYERLIB_EYERAVPACKETTEST_HPP
