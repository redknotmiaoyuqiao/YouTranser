#ifndef EYERLIB_PIXELFMTTEST_HPP
#define EYERLIB_PIXELFMTTEST_HPP

#include <stdio.h>
#include <gtest/gtest.h>

#include "EyerAVTranscoder/EyerAVTranscoderHeader.hpp"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class MyEyerAVTranscoderListener : public Eyer::EyerAVTranscoderListener
{
public:
    virtual int OnProgress(float progress) override
    {
        EyerLog("p: %f\n", progress);
        return 0;
    }

    virtual int OnFail(Eyer::EyerAVTranscoderError & error) override
    {
        return 0;
    }

    virtual int OnSuccess() override
    {
        return 0;
    }
};


TEST(EyerAVTranscoder, EyerAVTranscoderTest_Pixelfmt_AVC)
{
    Eyer::EyerString inputPath = "./panasonic_S5_h264_1920x1080_yuv420p_30fps_wedding2.MOV";
    Eyer::EyerAVDecoderBox decoderBox(inputPath);
    double duration = decoderBox.GetDuration();
    EyerLog("duration: %f\n", duration);

    Eyer::EyerAVTranscoderSupport support;
    std::vector<Eyer::EyerAVPixelFormat> pixels = support.QuerySupportPixelFormat(Eyer::EyerAVCodecID::CODEC_ID_H264);

    for(int j=0;j<pixels.size();j++){
        Eyer::EyerAVPixelFormat pixel = pixels[j];
        if(pixel == Eyer::EyerAVPixelFormat::EYER_KEEP_SAME){
            continue;
        }

        EyerLog("\tPixel Name: %s\n", pixel.GetDescName().c_str());

        Eyer::EyerString outputPath = Eyer::EyerString("./S5_h264_1920x1080_60fps_h264_") + pixel.GetDescName() + "_out.MP4";

        Eyer::EyerAVTranscoderParams params;
        params.SetVideoCodecId(Eyer::EyerAVCodecID::CODEC_ID_H264);
        params.SetVideoPixelFormat(pixel);

        params.SetAudioCodecId(Eyer::EyerAVCodecID::CODEC_ID_AAC);
        params.SetChannelLayout(Eyer::EyerAVChannelLayout::EYER_AV_CH_LAYOUT_STEREO);
        params.SetSampleRate(48000);

        MyEyerAVTranscoderListener listener;

        Eyer::EyerAVTranscoder transcoder(inputPath);
        transcoder.SetOutputPath(outputPath);
        transcoder.SetParams(params);
        transcoder.SetListener(&listener);
        int ret = transcoder.Transcode(nullptr);
        ASSERT_EQ(ret, 0);




        Eyer::EyerAVReader reader(outputPath);
        ret = reader.Open();
        ASSERT_EQ(ret, 0);
        int videoStreamIndex = reader.GetVideoStreamIndex();
        Eyer::EyerAVStream stream = reader.GetStream(videoStreamIndex);

        EyerLog("A: %s, B: %s\n", stream.GetPixelFormat().GetDescName().c_str(), pixel.GetDescName().c_str());
        if(pixel == Eyer::EyerAVPixelFormat::EYER_NV12){
            ASSERT_EQ(stream.GetPixelFormat(), Eyer::EyerAVPixelFormat::EYER_YUV420P);
        }
        else if(pixel == Eyer::EyerAVPixelFormat::EYER_NV21){
            ASSERT_EQ(stream.GetPixelFormat(), Eyer::EyerAVPixelFormat::EYER_YUV420P);
        }
        else if(pixel == Eyer::EyerAVPixelFormat::EYER_NV16){
            ASSERT_EQ(stream.GetPixelFormat(), Eyer::EyerAVPixelFormat::EYER_YUV422P);
        }
        else if(pixel == Eyer::EyerAVPixelFormat::EYER_NV20LE){
            ASSERT_EQ(stream.GetPixelFormat(), Eyer::EyerAVPixelFormat::EYER_YUV422P10LE);
        }
        else if(pixel == Eyer::EyerAVPixelFormat::EYER_GRAY8){
            ASSERT_EQ(stream.GetPixelFormat(), Eyer::EyerAVPixelFormat::EYER_YUV420P);
        }
        else if(pixel == Eyer::EyerAVPixelFormat::EYER_GRAY10LE){
            ASSERT_EQ(stream.GetPixelFormat(), Eyer::EyerAVPixelFormat::EYER_YUV420P10LE);
        }
        else {
            ASSERT_EQ(stream.GetPixelFormat(), pixel);
        }

        reader.Close();

        Eyer::EyerAVDecoderBox decoderBox(outputPath);

        Eyer::EyerAVFrame snapshotFrame;
        ret = decoderBox.GetFrame(snapshotFrame, duration / 2.0);
        ASSERT_EQ(ret, 0);

        EyerLog("Pixel Name: %s\n", pixel.GetDescName().c_str());
        EyerLog("Snapshot Frame: %s, width: %d, height: %d\n",
                snapshotFrame.GetPixelFormat().GetDescName().c_str(),
                snapshotFrame.GetWidth(),
                snapshotFrame.GetHeight());

        Eyer::EyerAVFrame snapshotRGBAFrame;
        snapshotFrame.Scale(snapshotRGBAFrame, Eyer::EyerAVPixelFormat::EYER_RGBA);

        Eyer::EyerAVImageWriter writer;
        Eyer::EyerString imageOutput = outputPath + ".png";
        writer.WriteFrame(snapshotRGBAFrame, imageOutput, Eyer::EyerAVPixelFormat::EYER_RGBA);

//        cv::Mat src = cv::imread(imageOutput.c_str());
//        cv::namedWindow(pixel.GetDescName().c_str());
//        cv::imshow(pixel.GetDescName().c_str(), src);
    }
}

TEST(EyerAVTranscoder, EyerAVTranscoderTest_Pixelfmt_HEVC)
{
    Eyer::EyerString inputPath = "./panasonic_S5_h264_1920x1080_yuv420p_30fps_wedding2.MOV";
    Eyer::EyerAVDecoderBox decoderBox(inputPath);
    double duration = decoderBox.GetDuration();
    Eyer::EyerAVFrame ff;
    decoderBox.GetFrame(ff, 0);
    int width = ff.GetWidth();
    int height = ff.GetHeight();
    EyerLog("duration: %f\n", duration);

    Eyer::EyerAVTranscoderSupport support;
    std::vector<Eyer::EyerAVPixelFormat> pixels = support.QuerySupportPixelFormat(Eyer::EyerAVCodecID::CODEC_ID_H265);

    for(int j=0;j<pixels.size();j++){
        EyerLog("\n");
        EyerLog("\n");
        EyerLog("==========================================================\n");
        EyerLog("\n");
        EyerLog("\n");

        Eyer::EyerAVPixelFormat pixel = pixels[j];
        if(pixel == Eyer::EyerAVPixelFormat::EYER_KEEP_SAME){
            continue;
        }

        EyerLog("\tPixel Name: %s\n", pixel.GetDescName().c_str());

        Eyer::EyerString outputPath =   Eyer::EyerString("./") + "S5_HEVC_" +
                                        Eyer::EyerString::Number(width) + "x" + Eyer::EyerString::Number(height) + "_" +
                                        pixel.GetDescName() + "_out.MP4";

        Eyer::EyerAVTranscoderParams params;
        params.SetVideoCodecId(Eyer::EyerAVCodecID::CODEC_ID_H265);
        params.SetVideoPixelFormat(pixel);

        params.SetAudioCodecId(Eyer::EyerAVCodecID::CODEC_ID_AAC);
        params.SetChannelLayout(Eyer::EyerAVChannelLayout::EYER_AV_CH_LAYOUT_STEREO);
        params.SetSampleRate(48000);

        MyEyerAVTranscoderListener listener;

        Eyer::EyerAVTranscoder transcoder(inputPath);
        transcoder.SetOutputPath(outputPath);
        transcoder.SetParams(params);
        transcoder.SetListener(&listener);
        transcoder.Transcode(nullptr);




        Eyer::EyerAVReader reader(outputPath);
        int ret = reader.Open();
        ASSERT_EQ(ret, 0);
        int videoStreamIndex = reader.GetVideoStreamIndex();
        Eyer::EyerAVStream stream = reader.GetStream(videoStreamIndex);

        EyerLog("A: %s, B: %s\n", stream.GetPixelFormat().GetDescName().c_str(), pixel.GetDescName().c_str());
        ASSERT_EQ(stream.GetPixelFormat(), pixel);

        reader.Close();

        Eyer::EyerAVDecoderBox decoderBox(outputPath);

        Eyer::EyerAVFrame snapshotFrame;
        ret = decoderBox.GetFrame(snapshotFrame, duration / 2.0);
        ASSERT_EQ(ret, 0);

        EyerLog("Pixel Name: %s\n", pixel.GetDescName().c_str());
        EyerLog("Snapshot Frame: %s, width: %d, height: %d\n",
                snapshotFrame.GetPixelFormat().GetDescName().c_str(),
                snapshotFrame.GetWidth(),
                snapshotFrame.GetHeight());

        Eyer::EyerAVFrame snapshotRGBAFrame;
        snapshotFrame.Scale(snapshotRGBAFrame, Eyer::EyerAVPixelFormat::EYER_RGBA);

        Eyer::EyerAVImageWriter writer;
        Eyer::EyerString imageOutput = outputPath + ".png";
        writer.WriteFrame(snapshotRGBAFrame, imageOutput, Eyer::EyerAVPixelFormat::EYER_RGBA);
    }
}


TEST(EyerAVTranscoder, EyerAVTranscoderTest_ALL_KEEPSAME_AAC)
{
    Eyer::EyerString inputPath = "./panasonic_S5_h264_1920x1080_yuv420p_30fps_wedding2.MOV";

    Eyer::EyerString outputPath =   Eyer::EyerString("./") + "S5_AVC_ALL_KEEP_SAME_AAC_out.MOV";

    Eyer::EyerAVTranscoderParams params;
    params.SetVideoCodecId(Eyer::EyerAVCodecID::CODEC_ID_H265);
    params.SetVideoPixelFormat(Eyer::EyerAVPixelFormat::EYER_KEEP_SAME);

    params.SetAudioCodecId(Eyer::EyerAVCodecID::CODEC_ID_AAC);
    params.SetChannelLayout(Eyer::EyerAVChannelLayout::EYER_KEEP_SAME);
    params.SetSampleRate(SAMPLE_RATE_KEEP_SAME);

    MyEyerAVTranscoderListener listener;

    Eyer::EyerAVTranscoder transcoder(inputPath);
    transcoder.SetOutputPath(outputPath);
    transcoder.SetParams(params);
    transcoder.SetListener(&listener);
    int ret = transcoder.Transcode(nullptr);
    if(ret){
        EyerLog("%s\n", transcoder.GetErrorDesc().c_str());
    }
    ASSERT_EQ(ret, 0);

    Eyer::EyerAVReader reader(outputPath);
    reader.Open();
    int audioIndex = reader.GetAudioStreamIndex();
    Eyer::EyerAVStream audioStream = reader.GetStream(audioIndex);

    ASSERT_EQ(audioStream.GetSampleRate(), 48000);
    ASSERT_EQ(audioStream.GetChannels(), 2);
    reader.Close();
}

TEST(EyerAVTranscoder, EyerAVTranscoderTest_ALL_KEEPSAME_MP3)
{
    Eyer::EyerString inputPath = "./panasonic_S5_h264_1920x1080_yuv420p_30fps_wedding2.MOV";

    Eyer::EyerString outputPath =   Eyer::EyerString("./") + "S5_AVC_ALL_KEEP_SAME_MP3_out.MOV";

    Eyer::EyerAVTranscoderParams params;
    params.SetVideoCodecId(Eyer::EyerAVCodecID::CODEC_ID_H264);
    params.SetVideoPixelFormat(Eyer::EyerAVPixelFormat::EYER_KEEP_SAME);

    params.SetAudioCodecId(Eyer::EyerAVCodecID::CODEC_ID_MP3);
    params.SetChannelLayout(Eyer::EyerAVChannelLayout::EYER_KEEP_SAME);
    params.SetSampleRate(SAMPLE_RATE_KEEP_SAME);

    MyEyerAVTranscoderListener listener;

    Eyer::EyerAVTranscoder transcoder(inputPath);
    transcoder.SetOutputPath(outputPath);
    transcoder.SetParams(params);
    transcoder.SetListener(&listener);
    transcoder.Transcode(nullptr);

    Eyer::EyerAVReader reader(outputPath);
    reader.Open();
    int audioIndex = reader.GetAudioStreamIndex();
    Eyer::EyerAVStream audioStream = reader.GetStream(audioIndex);

    ASSERT_EQ(audioStream.GetSampleRate(), 48000);
    ASSERT_EQ(audioStream.GetChannels(), 2);
    reader.Close();
}


TEST(EyerAVTranscoder, EyerAVTranscoderTest_ALL_KEEPSAME_PCMS32)
{
    Eyer::EyerString inputPath = "./panasonic_S5_h264_1920x1080_yuv420p_30fps_wedding2.MOV";

    Eyer::EyerString outputPath =   Eyer::EyerString("./") + "S5_AVC_ALL_KEEP_SAME_PCMS32_out.MOV";

    Eyer::EyerAVTranscoderParams params;
    params.SetVideoCodecId(Eyer::EyerAVCodecID::CODEC_ID_H265);
    params.SetVideoPixelFormat(Eyer::EyerAVPixelFormat::EYER_KEEP_SAME);

    params.SetAudioCodecId(Eyer::EyerAVCodecID::CODEC_ID_PCM_S32LE);
    params.SetChannelLayout(Eyer::EyerAVChannelLayout::EYER_KEEP_SAME);
    params.SetSampleRate(SAMPLE_RATE_KEEP_SAME);

    MyEyerAVTranscoderListener listener;

    Eyer::EyerAVTranscoder transcoder(inputPath);
    transcoder.SetOutputPath(outputPath);
    transcoder.SetParams(params);
    transcoder.SetListener(&listener);
    int ret = transcoder.Transcode(nullptr);
    if(ret){
        EyerLog("%s\n", transcoder.GetErrorDesc().c_str());
    }
    ASSERT_EQ(ret, 0);

    Eyer::EyerAVReader reader(outputPath);
    reader.Open();
    int audioIndex = reader.GetAudioStreamIndex();
    Eyer::EyerAVStream audioStream = reader.GetStream(audioIndex);

    ASSERT_EQ(audioStream.GetSampleRate(), 48000);
    ASSERT_EQ(audioStream.GetChannels(), 2);
    reader.Close();
}


TEST(EyerAVTranscoder, EyerAVTranscoderTest_ALL_KEEPSAME_PCMS16)
{
    Eyer::EyerString inputPath = "./panasonic_S5_h264_1920x1080_yuv420p_30fps_wedding2.MOV";

    Eyer::EyerString outputPath =   Eyer::EyerString("./") + "S5_AVC_ALL_KEEP_SAME_PCMS16_out.MOV";

    Eyer::EyerAVTranscoderParams params;
    params.SetVideoCodecId(Eyer::EyerAVCodecID::CODEC_ID_H265);
    params.SetVideoPixelFormat(Eyer::EyerAVPixelFormat::EYER_KEEP_SAME);

    params.SetAudioCodecId(Eyer::EyerAVCodecID::CODEC_ID_PCM_S16LE);
    params.SetChannelLayout(Eyer::EyerAVChannelLayout::EYER_KEEP_SAME);
    params.SetSampleRate(SAMPLE_RATE_KEEP_SAME);

    MyEyerAVTranscoderListener listener;

    Eyer::EyerAVTranscoder transcoder(inputPath);
    transcoder.SetOutputPath(outputPath);
    transcoder.SetParams(params);
    transcoder.SetListener(&listener);
    int ret = transcoder.Transcode(nullptr);
    if(ret){
        EyerLog("%s\n", transcoder.GetErrorDesc().c_str());
    }
    ASSERT_EQ(ret, 0);

    Eyer::EyerAVReader reader(outputPath);
    reader.Open();
    int audioIndex = reader.GetAudioStreamIndex();
    Eyer::EyerAVStream audioStream = reader.GetStream(audioIndex);

    ASSERT_EQ(audioStream.GetSampleRate(), 48000);
    ASSERT_EQ(audioStream.GetChannels(), 2);
    reader.Close();
}

#endif //EYERLIB_PIXELFMTTEST_HPP
