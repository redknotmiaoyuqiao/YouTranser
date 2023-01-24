#include "EyerAVAlphaFrameUtil.hpp"

namespace Eyer
{
    EyerAVAlphaFrameUtil::EyerAVAlphaFrameUtil()
    {

    }

    EyerAVAlphaFrameUtil::~EyerAVAlphaFrameUtil()
    {

    }

    EyerAVFrame EyerAVAlphaFrameUtil::Convert(EyerAVFrame & frame)
    {
        EyerAVFrame frame422p;
        frame422p.SetWidth(frame.GetWidth());
        frame422p.SetHeight(frame.GetHeight());
        frame422p.SetPixelFormat(EyerAVPixelFormat::EYER_YUV422P);
        frame422p.GetBuffer(1);

        EyerAVFrame frame420p;
        frame.Scale(frame420p, EyerAVPixelFormat::EYER_YUV420P);

        // copy y channel
        for(int i=0;i<frame420p.GetHeight();i++){
            uint8_t * dist = frame422p.GetData(0);
            int distLinesize = frame422p.GetLinesize(0);
            uint8_t * src = frame420p.GetData(0);
            int srcLinesize = frame420p.GetLinesize(0);

            memcpy(dist + distLinesize * i, src + srcLinesize * i, frame420p.GetWidth());
        }

        // cpoy uv channelvv

        return frame422p;
    }
}