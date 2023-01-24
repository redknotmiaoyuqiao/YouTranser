#ifndef EYERLIB_EYERAVTRANSCODETEST_HPP
#define EYERLIB_EYERAVTRANSCODETEST_HPP

#include <gtest/gtest.h>
#include "EyerAV/EyerAV.hpp"

/*
TEST(EyerAV, EyerAVTranscodeTest)
{
    Eyer::EyerAVTranscodeParams params;
    params.targetWidth = 800;
    params.targetHeight = 480;
    params.fps = 60;
    // Eyer::EyerAVTranscode transcode("https://www.zzsin.com/hdr/ZhongLi.mp4", "./demo_out_800_480.mp4", params);
    // Eyer::EyerAVTranscode transcode("/Users/miaoyuqiao/Desktop/HDR/Uzi.mp4", "./demo_out_800_480.mp4", params);
    // Eyer::EyerAVTranscode transcode("https://www.zzsin.com/hdr/Uzi.mp4", "./demo_out_800_480.mp4", params);
    // Eyer::EyerAVTranscode transcode("./demo.mp4", "./demo_out_800_480.mp4", params);
    // Eyer::EyerAVTranscode transcode("/Users/miaoyuqiao/Desktop/HDR/ZhongLi.mp4", "/Users/miaoyuqiao/Desktop/HDR/ZhongLi_tt.mp4", params);
    // Eyer::EyerAVTranscode transcode("/Users/redknot/DemoVideo/video1.mp4", "/Users/redknot/DemoVideo/video1_out.mp4", params);
    // Eyer::EyerAVTranscode transcode("/Users/redknot/DemoVideo/video2.mp4", "/Users/redknot/DemoVideo/video2_out.mp4", params);
    // transcode.Transcode();

    params.careAudio = true;
    params.careVideo = true;
    // Eyer::EyerAVTranscode transcode2("/Users/miaoyuqiao/VVV/veilside.aac", "./aaa.mp3", params);
    // Eyer::EyerAVTranscode transcode2("./test_image.jpg", "./demo_out.jpg", params);

    // Eyer::EyerAVTranscode transcode2("/Users/miaoyuqiao/aaa.mp4", "./aaa.mp4", params);
    Eyer::EyerAVTranscode transcode2("./ZhongLi.mp4", "./aaa.mp4", params);
    transcode2.Transcode();
}

TEST(EyerAV, EyerAVTranscode_JPEG_Test)
{
    Eyer::EyerAVTranscodeParams params;
    params.targetWidth = 1920;
    params.targetHeight = 1080;
    params.fps = 60;
    params.careAudio = true;
    params.careVideo = true;
    Eyer::EyerAVTranscode transcode("./test_image.jpg", "./demo_jpeg_1920_1080_out.jpg", params);
    transcode.Transcode();
}

TEST(EyerAV, EyerAVTranscode_PNG_Test)
{
    Eyer::EyerAVTranscodeParams params;
    params.targetWidth = 1920;
    params.targetHeight = 1080;
    params.fps = 60;
    params.careAudio = true;
    params.careVideo = true;
    Eyer::EyerAVTranscode transcode("./test_image.png", "./demo_png_1920_1080_out.png", params);
    transcode.Transcode();
}

TEST(EyerAV, EyerAVTranscode_264_Test)
{
    Eyer::EyerAVTranscodeParams params;
    params.targetWidth = 640;
    params.targetHeight = 360;
    params.fps = 30;
    params.careAudio = true;
    params.careVideo = true;
    Eyer::EyerAVTranscode transcode("./ZhongLi.mp4", "./ZhongLi_out_1920_1080_out.mp4", params);
    transcode.Transcode();
}

TEST(EyerAV, EyerAVTranscode_264_Audio_Only_Test)
{
    Eyer::EyerAVTranscodeParams params;
    params.targetWidth = 640;
    params.targetHeight = 360;
    params.fps = 30;
    params.careAudio = true;
    params.careVideo = false;
    Eyer::EyerAVTranscode transcode("./ZhongLi.mp4", "./ZhongLi_out_44100_out.mp3", params);
    transcode.Transcode();
}

TEST(EyerAV, EyerAVTranscode_MP3_Audio_Only_Test)
{
    Eyer::EyerAVTranscodeParams params;
    params.targetWidth = 640;
    params.targetHeight = 360;
    params.fps = 30;
    params.careAudio = true;
    params.careVideo = true;
    Eyer::EyerAVTranscode transcode("./ZhongLi_44100.mp3", "./ZhongLi_out_44100_audio_out.mp3", params);
    transcode.Transcode();
}

TEST(EyerAV, EyerAVTranscode_FLAC_Audio_Only_Test)
{
    Eyer::EyerAVTranscodeParams params;
    params.targetWidth = 640;
    params.targetHeight = 360;
    params.fps = 30;
    params.careAudio = true;
    params.careVideo = true;
    Eyer::EyerAVTranscode transcode("./zhaolei_wojide.flac", "./zhaolei_wojide.mp3", params);
    transcode.Transcode();
}

TEST(EyerAV, EyerAVTranscode_FLAC_Test)
{
    Eyer::EyerAVTranscodeParams params;
    params.targetWidth = 640;
    params.targetHeight = 360;
    params.fps = 30;
    params.careAudio = true;
    params.careVideo = true;
    Eyer::EyerAVTranscode transcode("/Users/bytedance/Downloads/zhaolei_wojide.flac", "./zhaolei_wojide.flac.mp3", params);
    transcode.Transcode();
}
*/

TEST(EyerAV, EyerAVTranscode_FLAC_Test)
{
    Eyer::EyerAVTranscodeParams params;
    params.targetWidth = 640;
    params.targetHeight = 360;
    params.fps = 30;
    params.careAudio = true;
    params.careVideo = true;
    Eyer::EyerAVTranscode transcode("/Users/bytedance/Downloads/zhaolei_wojide.flac", "./zhaolei_wojide.flac.mp3", params);
    transcode.Transcode();
}

#endif //EYERLIB_EYERAVTRANSCODETEST_HPP
