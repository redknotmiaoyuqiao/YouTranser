#include "EyerAVAudioBox.hpp"

namespace Eyer
{
    EyerAVAudioBox::EyerAVAudioBox(const EyerString & _path,
                                   EyerAVReaderCustomIO * _customIO,
                                   int64_t _sampleOffset,
                                   EyerAVChannelLayout _channelLayout,
                                   EyerAVSampleFormat _sampleFormat,
                                   int _samplerate
                                   )
        : path(_path)
        , sampleOffset(_sampleOffset)
        , channelLayout(_channelLayout)
        , sampleFormat(_sampleFormat)
        , samplerate(_samplerate)
    {
        reader = new EyerAVReader(path, _customIO);
        int ret = reader->Open();
        if(ret){
            EyerLogE("EyerAVAudioBox Open fail: %d, url: %s\n", ret, path.c_str());
            return;
        }
        audioIndex = reader->GetAudioStreamIndex();
        if(audioIndex < 0){
            EyerLogE("EyerAVAudioBox No Audio Stream, url: %s\n", path.c_str());
            return;
        }
        EyerAVStream stream = reader->GetStream(audioIndex);
        decoder = new EyerAVDecoder();
        decoder->Init(stream);

        resample = new EyerAVResample();
        EyerAVChannelLayout inputChannelLayout = stream.GetChannelLayout();
        if(inputChannelLayout == EyerAVChannelLayout::UNKNOW){
            inputChannelLayout = EyerAVChannelLayout::GetDefaultChannelLayout(stream.GetChannels());
        }
        resample->Init(
                channelLayout,
                sampleFormat,
                samplerate,

                inputChannelLayout,
                stream.GetSampleFormat(),
                stream.GetSampleRate()
        );

        if(sampleOffset > 0){
            EyerAVRational timebase = stream.GetTimebase();
            int64_t t = sampleOffset * 1.0 / 48000 * timebase.den / timebase.num;
            EyerLog("Seek Time: %lld\n", sampleOffset);
            EyerLog("%d / %d\n", timebase.num, timebase.den);
            EyerLog("Seek Time: %lld\n", t);

            reader->SeekStream(t, audioIndex);
        }
    }

    EyerAVAudioBox::~EyerAVAudioBox()
    {
        if(resample != nullptr){
            delete resample;
            resample = nullptr;
        }
        if(decoder != nullptr){
            delete decoder;
            decoder = nullptr;
        }
        if(reader != nullptr){
            delete reader;
            reader = nullptr;
        }
    }

    int EyerAVAudioBox::GetFrame(EyerAVFrame & frame, int wanLen, bool * isEnd)
    {
        if(audioIndex >= 0 && resample != nullptr && decoder != nullptr && decoder != nullptr) {
            while (1) {
                int ret = resample->GetFrame(frame, wanLen);
                if (!ret) {
                    break;
                }

                EyerAVPacket packet;
                ret = reader->Read(packet);

                if (ret) {
                    break;
                }

                if (packet.GetStreamIndex() != audioIndex) {
                    continue;
                }

                decoder->SendPacket(packet);
                while (1) {
                    EyerAVFrame avFrame;
                    ret = decoder->RecvFrame(avFrame);
                    if (ret) {
                        break;
                    }

                    if(sampleOffset * 1.0 / samplerate > avFrame.GetSecPTS()){
                        continue;
                    }

                    resample->PutAVFrame(avFrame);
                }
            }
        }

        if(frame.GetSampleNB() <= 0){
            if(isEnd != nullptr){
                *isEnd = true;
            }
            frame.SetChannelLayout(channelLayout);
            frame.SetSampleFormat(sampleFormat);
            frame.SetSampleRate(samplerate);
            frame.SetSampleNB(1024);
            frame.GetBuffer(0);

            int channel = Eyer::EyerAVChannelLayout::GetChannelLayoutNBChannels(frame.GetChannelLayout());

            float * dist = (float *)frame.GetData();
            for(int i = 0;i<frame.GetSampleNB();i++){
                dist[i * channel + 0] = 0;
                dist[i * channel + 1] = 0;
            }
        }
        else {
            if(isEnd != nullptr){
                *isEnd = false;
            }
        }

        return 0;
    }
}