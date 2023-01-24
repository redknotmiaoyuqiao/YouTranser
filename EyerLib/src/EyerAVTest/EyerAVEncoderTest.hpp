#ifndef EYERLIB_EYERAVENCODERTEST_HPP
#define EYERLIB_EYERAVENCODERTEST_HPP

#include <gtest/gtest.h>
#include "EyerAV/EyerAV.hpp"

TEST(EyerAV, EyerAVEncoderTest)
{
    int width       = 1920;
    int height      = 1080;
    int fps         = 60;

    Eyer::EyerAVEncoderParam encoderParam;
    encoderParam.InitH264(width, height, {1, fps});

    Eyer::EyerAVEncoder h264Encoder;
    int ret = h264Encoder.Init(encoderParam);
    EyerLog("Encoder Init: %d\n", ret);
    if(ret){
        return;
    }

    Eyer::EyerAVWriter writer("./demo_out.mp4");
    writer.Open();
    int writerStreamId = writer.AddStream(h264Encoder);
    writer.WriteHand();

    Eyer::EyerAVRational encoderTimebase;
    h264Encoder.GetTimebase(encoderTimebase);

    Eyer::EyerAVRational streamTimebase;
    writer.GetTimebase(streamTimebase, writerStreamId);

    unsigned char * y = (unsigned char *)malloc(width * height);
    unsigned char * u = (unsigned char *)malloc(width / 2 * height / 2);
    unsigned char * v = (unsigned char *)malloc(width / 2 * height / 2);

    int frameCount = fps * 10;

    for(int i=0; i<frameCount; i++){
        Eyer::EyerAVFrame frame;

        memset(y, 0, width * height);

        float scale = (i * 1.0f) / frameCount;
        int start = (int)(scale * height);

        for(int j=start; j<start+100; j++){
            if(j >= height){
                break;
            }
            memset(y + j * width, 200, width);
        }

        memset(u, 127, width / 2 * height / 2);
        memset(v, 0, width / 2 * height / 2);

        frame.SetVideoData420P(y, u, v, width, height);
        frame.SetPTS(i);

        ret = h264Encoder.SendFrame(frame);
        if(ret){
            continue;
        }
        while(1){
            Eyer::EyerAVPacket packet;
            ret = h264Encoder.RecvPacket(packet);
            if(ret){
                break;
            }
            packet.SetStreamIndex(writerStreamId);
            packet.RescaleTs(encoderTimebase, streamTimebase);

            writer.WritePacket(packet);
        }
    }

    h264Encoder.SendFrameNull();
    while(1){
        Eyer::EyerAVPacket packet;
        ret = h264Encoder.RecvPacket(packet);
        if(ret){
            break;
        }
        packet.SetStreamIndex(writerStreamId);
        packet.RescaleTs(encoderTimebase, streamTimebase);

        writer.WritePacket(packet);
    }

    free(y);
    free(u);
    free(v);

    writer.WriteTrailer();
    writer.Close();
}

#endif //EYERLIB_EYERAVENCODERTEST_HPP
