#include "EyerImageUtil.hpp"

#include "EyerAVEncoder.hpp"
#include "EyerAVWriter.hpp"

namespace Eyer
{
    int EyerImageUtil::WriteFrame(EyerAVFrame & frame, const EyerString & path)
    {
        // Frame 格式转换
        EyerAVFrame frameYUV420P;
        int ret = frame.Scale(frameYUV420P, EyerAVPixelFormat::EYER_YUV420P);
        if(ret){
            EyerLog("Image Scale Fail\n");
            return -1;
        }


        EyerAVEncoder imageEncode;
        EyerAVEncoderParam param;
        param.InitJPEG(frameYUV420P.GetWidth(), frameYUV420P.GetHeight());
        ret = imageEncode.Init(param);
        if(ret){
            EyerLog("Image Encoder Init Fail\n");
            return -2;
        }

        EyerAVWriter writer(path);
        writer.Open();
        int streamId = writer.AddStream(imageEncode);
        writer.WriteHand();

        imageEncode.SendFrame(frameYUV420P);
        while(1){
            EyerAVPacket packet;
            ret = imageEncode.RecvPacket(packet);
            if(ret){
                break;
            }

            packet.SetStreamIndex(streamId);
            writer.WritePacket(packet);
        }

        writer.WriteTrailer();
        writer.Close();

        return 0;
    }
}