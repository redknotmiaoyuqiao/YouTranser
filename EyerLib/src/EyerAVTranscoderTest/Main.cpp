#include <stdio.h>
#include <gtest/gtest.h>

#include <filesystem>

#include "EyerAVTranscoder/EyerAVTranscoderHeader.hpp"

TEST(EyerAVTranscoder, EyerAVTranscoderQuerySupport)
{
    Eyer::EyerAVTranscoderSupport support;
    std::vector<Eyer::EyerAVFileFmt> fmts = support.QuerySupportFmt();
    for(int i=0;i<fmts.size();i++){
        fmts[i].GetDesc();
        fmts[i].GetSuffix();

        std::vector<Eyer::EyerAVCodecID> videoCodecs = support.QuerySupportVideoCodec(fmts[i]);
        EyerLog("Video Codec List:\n");
        for(int i=0;i<videoCodecs.size();i++){
            Eyer::EyerAVCodecID codecId = videoCodecs[i];
            EyerLog("\tCodec ID: %s\n", codecId.GetName().c_str());

            std::vector<Eyer::EyerAVPixelFormat> pixels = support.QuerySupportPixelFormat(codecId);
            for(int j=0;j<pixels.size();j++){
                Eyer::EyerAVPixelFormat pixel = pixels[j];
                EyerLog("\t\tPixel Format: %s\n", pixel.GetName().c_str());
            }
        }

        std::vector<Eyer::EyerAVCodecID> audioCodecs = support.QuerySupportAudioCodec(fmts[i]);
        EyerLog("Audio Codec List:\n");
        for(int i=0;i<audioCodecs.size();i++){
            Eyer::EyerAVCodecID codecId = audioCodecs[i];
            EyerLog("\tCodec ID: %s\n", codecId.GetName().c_str());
            std::vector<Eyer::EyerAVChannelLayout> channelLayouts = support.QuerySupportChannelLayout(codecId);
            for(int j=0;j<channelLayouts.size();j++){
                Eyer::EyerAVChannelLayout channelLayout = channelLayouts[j];
                EyerLog("\t\tChannel Layout: %s\n", channelLayout.GetName().c_str());
            }

            std::vector<int> sampleRates = support.QuerySupportSampleRate(codecId);
            for(int j=0;j<sampleRates.size();j++){
                int sampleRate = sampleRates[j];
                EyerLog("\t\tSample Rate: %d\n", sampleRate);
            }
        }
    }
}

#include "PixelFmtTest.hpp"

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}