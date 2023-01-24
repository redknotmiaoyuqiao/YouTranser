#include "EyerAVImageWriter.hpp"

#include "EyerAVEncoderParam.hpp"
#include "EyerAVEncoder.hpp"
#include "EyerAVWriter.hpp"

namespace Eyer
{
    EyerAVImageWriter::EyerAVImageWriter()
    {

    }

    EyerAVImageWriter::~EyerAVImageWriter()
    {

    }

    int EyerAVImageWriter::WriteFrame(EyerAVFrame & frame, const EyerString & path, const EyerAVPixelFormat & pixelFormat)
    {
        int width = frame.GetWidth();
        int height = frame.GetHeight();

        EyerAVEncoderParam encoderParam;
        encoderParam.InitPNG(width, height, pixelFormat);

        EyerAVEncoder encoder;
        int ret = encoder.Init(encoderParam);
        if(ret){
            return -1;
        }

        EyerAVWriter writer(path);
        writer.Open();
        writer.AddStream(encoder);
        writer.WriteHand();

        encoder.SendFrame(frame);
        while(1){
            EyerAVPacket packet;
            ret = encoder.RecvPacket(packet);
            if(ret){
                break;
            }

            writer.WritePacket(packet);
            // EyerLog("len: %d\n", packet.GetSize());
        }

        writer.WriteTrailer();
        writer.Close();

        return 0;
    }
}