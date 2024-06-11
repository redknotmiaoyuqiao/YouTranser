#include "EyerAVVideoWriter.hpp"

namespace Eyer
{
    EyerAVVideoWriter::EyerAVVideoWriter(const EyerString & path, int width, int height, int fps)
        : mPath(path)
        , writer(path)
    {
        EyerAVEncoderParam param;
        param.InitH264(width, height, fps, EyerAVPixelFormat::EYER_YUV420P, 17);
        encoder.Init(param);

        writer.Open();

        videoStreamIndex = writer.AddStream(encoder);
        writer.WriteHand();
    }

    EyerAVVideoWriter::~EyerAVVideoWriter()
    {
        encoder.SendFrameNull();
        while(1){
            Eyer::EyerAVPacket pkg;
            int ret = encoder.RecvPacket(pkg);
            if(ret){
                break;
            }
            pkg.SetStreamIndex(videoStreamIndex);
            pkg.RescaleTs(encoder.GetTimebase(), writer.GetTimebase(videoStreamIndex));
            writer.WritePacket(pkg);
        }

        writer.WriteTrailer();
        writer.Close();
    }

    int EyerAVVideoWriter::PutFrame(const EyerAVFrame & frame, int64_t frameIndex)
    {
        Eyer::EyerAVFrame yuvframe;
        frame.Scale(yuvframe, Eyer::EyerAVPixelFormat::EYER_YUV420P);

        EyerLog("%d, %d\n", yuvframe.GetWidth(), yuvframe.GetHeight());
        yuvframe.SetPTS(frameIndex);

        encoder.SendFrame(yuvframe);
        while(1){
            Eyer::EyerAVPacket pkg;
            int ret = encoder.RecvPacket(pkg);
            if(ret){
                break;
            }
            pkg.SetStreamIndex(videoStreamIndex);
            pkg.RescaleTs(encoder.GetTimebase(), writer.GetTimebase(videoStreamIndex));
            writer.WritePacket(pkg);
        }
        return 0;
    }
}