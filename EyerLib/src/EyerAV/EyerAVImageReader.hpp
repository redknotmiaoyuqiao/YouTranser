#ifndef EYERLIB_EYERAVIMAGEREADER_HPP
#define EYERLIB_EYERAVIMAGEREADER_HPP

#include "EyerAVFrame.hpp"
#include "EyerCore/EyerCore.hpp"
#include "EyerAVReaderCustomIO.hpp"

namespace Eyer
{
    class EyerAVImageReader
    {
    public:
        EyerAVImageReader();
        ~EyerAVImageReader();

        int ReadFrame(EyerAVFrame & frame, const EyerString & path, EyerAVReaderCustomIO * _customIO = nullptr);
    };
}

#endif //EYERLIB_EYERAVIMAGEREADER_HPP
