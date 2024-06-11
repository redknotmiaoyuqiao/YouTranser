#ifndef EYERLIB_EYERAVVIDEOWRITER_HPP
#define EYERLIB_EYERAVVIDEOWRITER_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerAVFrame.hpp"
#include "EyerAVEncoder.hpp"
#include "EyerAVWriter.hpp"

namespace Eyer
{
    class EyerAVVideoWriter
    {
    public:
        EyerAVVideoWriter(const EyerString & path, int width, int height, int fps);
        ~EyerAVVideoWriter();

        int PutFrame(const EyerAVFrame & frame, int64_t frameIndex);

    private:
        EyerString mPath = "";
        EyerAVEncoder encoder;

        EyerAVWriter writer;
        int videoStreamIndex = -1;
    };
}



#endif //EYERLIB_EYERAVVIDEOWRITER_HPP
