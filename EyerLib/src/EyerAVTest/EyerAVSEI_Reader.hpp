#ifndef EYERLIB_EYERAVSEI_READER_HPP
#define EYERLIB_EYERAVSEI_READER_HPP

#include <gtest/gtest.h>
#include "EyerAV/EyerAV.hpp"

/*
TEST(EyerAV, EyerAV_WRITE_SEI_Test)
{
    Eyer::EyerAVReader reader("./demo.mp4");
    int ret = reader.Open();
    ASSERT_EQ(ret, 0);

    int videoStreamIndex = reader.GetVideoStreamIndex();
    int audioStreamIndex = reader.GetAudioStreamIndex();

    Eyer::EyerAVStream stream;
    reader.GetStream(stream, videoStreamIndex);

    Eyer::EyerAVBitstreamFilter filter(Eyer::EyerAVBitstreamFilterType::H264_METADATA, stream);

    while(1){
        Eyer::EyerAVPacket packet;
        ret = reader.Read(packet);
        if(ret){
            break;
        }

        if(packet.GetStreamIndex() != videoStreamIndex){
            continue;
        }

        // EyerLog("InputPacket: %d\n", packet.GetSize());

        filter.SendPacket(packet);
        while(1){
            Eyer::EyerAVPacket outPacket;
            ret = filter.RecvPacket(outPacket);
            if(ret){
                break;
            }

            if(outPacket.GetSize() != packet.GetSize()){
                // EyerLog("InputPacket: %d, OutputSize: %d\n", packet.GetSize(), outPacket.GetSize());
            }
        }
    }

    reader.Close();
}
*/

TEST(EyerAV, EyerAV_READ_SEI_Test)
{
    // Eyer::EyerAVReader reader("./demo_video.h264");
    Eyer::EyerAVReader reader("./demo.mp4");
    int ret = reader.Open();
    ASSERT_EQ(ret, 0);

    int videoStreamIndex = reader.GetVideoStreamIndex();
    int audioStreamIndex = reader.GetAudioStreamIndex();

    Eyer::EyerAVStream stream;
    reader.GetStream(stream, videoStreamIndex);

    Eyer::EyerAVBitstreamFilter filter(Eyer::EyerAVBitstreamFilterType::H264_MP4TOANNEXB, stream);

    while(1){
        Eyer::EyerAVPacket packet;
        ret = reader.Read(packet);
        if(ret){
            break;
        }

        if(packet.GetStreamIndex() != videoStreamIndex){
            continue;
        }

        filter.SendPacket(packet);

        while(1){
            Eyer::EyerAVPacket outPacket;
            ret = filter.RecvPacket(outPacket);
            if(ret){
                break;
            }

            int size = outPacket.GetSize();

            uint8_t * d = outPacket.GetDatePtr();
            // EyerLog("OutPacket: %d\n", size);

            int startCodeLen = 4;
            int forbidden_bit   = (*(d + startCodeLen) >> 7) & 1;
            int nal_ref_idc     = (*(d + startCodeLen) >> 5) & 3;
            int nal_unit_type   = (*(d + startCodeLen) >> 0) & 0x1f;

            if(nal_unit_type == 6){
                printf("%d %d %d %d %d\n", d[0], d[1], d[2], d[3], d[4]);
                for(int i=0;i<60;i++){
                    printf("%c", d[i]);
                }
                printf("\n");
            }
        }
    }

    reader.Close();
}

#endif //EYERLIB_EYERAVSEI_READER_HPP
