#include "EyerAVImageReader.hpp"

#include "EyerAVReader.hpp"
#include "EyerAVDecoder.hpp"

namespace Eyer
{
    EyerAVImageReader::EyerAVImageReader()
    {

    }

    EyerAVImageReader::~EyerAVImageReader()
    {

    }

    int EyerAVImageReader::ReadFrame(EyerAVFrame & frame, const EyerString & path)
    {
        EyerAVReader reader(path);
        int ret = reader.Open();
        if(ret){
            return -1;
        }

        int videoStreamIndex = reader.GetVideoStreamIndex();
        if(videoStreamIndex < 0){
            return -2;
        }

        EyerAVStream stream;
        ret = reader.GetStream(stream, videoStreamIndex);
        if(ret){
            return -3;
        }

        EyerAVDecoder decoder;
        ret = decoder.Init(stream);
        if(ret){
            return -4;
        }

        int frameIndex = 0;

        while(1){
            EyerAVPacket packet;
            ret = reader.Read(packet);
            if(ret){
                break;
            }

            if(packet.GetStreamIndex() != videoStreamIndex){
                continue;
            }

            ret = decoder.SendPacket(packet);
            if(ret){
                break;
            }
            while(1){
                EyerAVFrame tempFrame;
                ret = decoder.RecvFrame(tempFrame);
                if(ret){
                    break;
                }

                frame = tempFrame;
                frameIndex++;
            }
        }

        ret = decoder.SendPacketNull();
        while(1){
            EyerAVFrame tempFrame;
            ret = decoder.RecvFrame(tempFrame);
            if(ret){
                break;
            }

            frame = tempFrame;
            frameIndex++;
        }

        reader.Close();

        if(frameIndex <= 0){
            return -5;
        }

        return 0;
    }
}