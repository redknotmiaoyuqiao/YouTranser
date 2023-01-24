#ifndef EYERLIB_EYERAVWRITER_AVAV_HPP
#define EYERLIB_EYERAVWRITER_AVAV_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerAVPacket.hpp"
#include "EyerAVEncoder.hpp"

namespace Eyer
{
    class EyerAVWriterPrivate;

    class EyerAVWriter {
    public:
        EyerAVWriter(const EyerString _path);
        ~EyerAVWriter();

        int Open();
        int Close();

        int AddStream(EyerAVEncoder & encoder);

        int GetTimebase(EyerAVRational & timebase, int streamIndex);
        EyerAVRational GetTimebase(int streamIndex);

        int WriteHand();
        int WriteTrailer();

        int WritePacket(EyerAVPacket & packet);
    public:
        EyerAVWriterPrivate * piml = nullptr;
    };
}

#endif //EYERLIB_EYERAVWRITER_HPP
