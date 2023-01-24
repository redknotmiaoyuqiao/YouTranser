#ifndef EYERLIB_EYERAVBITSTREAMFILTERTEST_HPP
#define EYERLIB_EYERAVBITSTREAMFILTERTEST_HPP

#include <gtest/gtest.h>
#include "EyerAV/EyerAV.hpp"

TEST(EyerAV, AVBitstreamFilterTest)
{
    Eyer::EyerAVBitstreamFilter::QueryAllBitstreamFilter();

    Eyer::EyerAVReader reader("./demo.mp4");
    int ret = reader.Open();
    ASSERT_EQ(ret, 0) << "EyerAVReader Open Error\n";
    if(ret){
        return;
    }

    Eyer::EyerAVStream stream;
    reader.GetStream(stream, 0);

    Eyer::EyerAVBitstreamFilter * bitstreamFilter = new Eyer::EyerAVBitstreamFilter(Eyer::EyerAVBitstreamFilterType::H264_MP4TOANNEXB, stream);


    while(1){
        Eyer::EyerAVPacket packet;
        ret = reader.Read(packet);
        if(ret){
            break;
        }

        int streamIndex = packet.GetStreamIndex();
        if(streamIndex == 0){
            uint8_t * dataPtr = packet.GetDatePtr();
            EyerLog("avcC %d %d %d %d %d\n", dataPtr[0], dataPtr[1], dataPtr[2], dataPtr[3], dataPtr[4]);

            bitstreamFilter->SendPacket(packet);
            while(1){
                Eyer::EyerAVPacket annexBPacket;
                ret = bitstreamFilter->RecvPacket(annexBPacket);
                if(ret){
                    break;
                }
                uint8_t * dataPtr = annexBPacket.GetDatePtr();
                EyerLog("annexB %d %d %d %d %d\n", dataPtr[0], dataPtr[1], dataPtr[2], dataPtr[3], dataPtr[4]);
            }
        }
    }

    delete bitstreamFilter;

    ret = reader.Close();
    ASSERT_EQ(ret, 0) << "EyerAVReader Close Error\n";
    if(ret){
        return;
    }
}

#endif //EYERLIB_EYERAVBITSTREAMFILTERTEST_HPP
