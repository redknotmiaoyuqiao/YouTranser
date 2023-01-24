#include "EyerAVDecoderLineAudio.hpp"

#include "EyerAVReader.hpp"
#include "EyerAVDecoder.hpp"
#include "EyerAVFrame.hpp"

#include <math.h>

namespace Eyer
{
    EyerAVDecoderLineAudio::EyerAVDecoderLineAudio(const EyerString & _path,  const EyerString & _cacheFilePath)
        : path(_path)
        , cacheFilePath(_cacheFilePath)
    {
        // 先全转换完毕，用的时候速度快，后期再优化
        EyerAVReader reader(path);
        int ret = reader.Open();
        if(ret){
            return;
        }
        int audioStreamId = reader.GetAudioStreamIndex();
        if(audioStreamId < 0){
            return;
        }

        EyerAVStream audioStream = reader.GetStream(audioStreamId);
        EyerAVRational timebase = audioStream.GetTimebase();

        EyerLog("num / den : %d / %d\n", timebase.num, timebase.den);

        EyerAVDecoder decoder;
        ret = decoder.Init(audioStream);
        if(ret){
            return;
        }

        FILE * file = fopen(cacheFilePath.c_str(), "wb");

        while(1){
            EyerAVPacket packet;
            ret = reader.Read(packet);
            if(ret){
                break;
            }

            if(packet.GetStreamIndex() != audioStreamId){
                continue;
            }

            decoder.SendPacket(packet);
            while(1){
                EyerAVFrame avFrame;
                ret = decoder.RecvFrame(avFrame);
                if(ret){
                    break;
                }

                ProgressFrame(avFrame, file);
            }
        }

        decoder.SendPacketNull();
        while(1){
            EyerAVFrame avFrame;
            ret = decoder.RecvFrame(avFrame);
            if(ret){
                break;
            }
            ProgressFrame(avFrame, file);
        }

        if(file != nullptr){
            fclose(file);
            file = nullptr;
        }

        reader.Close();
    }

    EyerAVDecoderLineAudio::~EyerAVDecoderLineAudio()
    {
        if(resample != nullptr){
            delete resample;
            resample = nullptr;
        }
    }

    int EyerAVDecoderLineAudio::GetFrame(EyerAVFrame & distFrame, int offset, int length)
    {
        int channles = EyerAVChannelLayout::GetChannelLayoutNBChannels(EyerAVChannelLayout::EYER_AV_CH_LAYOUT_STEREO);

        distFrame.InitAudioData(EyerAVChannelLayout::EYER_AV_CH_LAYOUT_STEREO, EyerAVSampleFormat::SAMPLE_FMT_FLT, 44100, length);

        // return resample->GetFrame(distFrame, length);

        FILE * file = fopen(cacheFilePath.c_str(), "rb");

        if(file == nullptr){
            return -1;
        }

        fseek(file, offset * channles * sizeof(float), SEEK_SET);

        int len = length * channles * sizeof(float);
        int ret = fread((uint8_t *)distFrame.GetData(), len, 1, file);

        fclose(file);

        if(ret <= 0){
            return -1;
        }

        return 0;
    }

    int EyerAVDecoderLineAudio::ProgressFrame(EyerAVFrame & avFrame, FILE * cacheFile)
    {
        EyerAVSampleFormat outSampleFormat = EyerAVSampleFormat::SAMPLE_FMT_FLT;
        EyerAVChannelLayout outChannelLayout = EyerAVChannelLayout::EYER_AV_CH_LAYOUT_STEREO;

        if(resample == nullptr){
            resample = new EyerAVResample();
            resample->Init(
                    outChannelLayout,
                    outSampleFormat,
                    44100,

                    avFrame.GetChannelLayout(),
                    avFrame.GetSampleFormat(),
                    avFrame.GetSampleRate()
                    );
        }

        resample->PutAVFrame(avFrame);

        while(1){
            int outSize = 1024;
            EyerAVFrame outframe;
            int ret = resample->GetFrame(outframe, outSize);
            if(ret < 0){
                break;
            }

            int channles = EyerAVChannelLayout::GetChannelLayoutNBChannels(outChannelLayout);

            fwrite(outframe.GetData(0), outSize * channles * sizeof(float), 1, cacheFile);
            sampleCount += outSize;
        }

        // EyerLog("Audio Frame: %lld\n", avFrame.GetPTS());
        return 0;
    }

    long long EyerAVDecoderLineAudio::GetSampleCount()
    {
        return sampleCount;
    }
}