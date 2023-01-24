#ifndef EYERLIB_EYERAVPACKET_HPP
#define EYERLIB_EYERAVPACKET_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerAVRational.hpp"

namespace Eyer
{
    class EyerAVPacketPrivate;

    class EyerAVPacket
    {
    public:
        EyerAVPacket();
        EyerAVPacket(const EyerAVPacket & packet);
        ~EyerAVPacket();

        EyerAVPacket & operator = (const EyerAVPacket & packet);

        int64_t GetPTS();

        int GetStreamIndex();
        int SetStreamIndex(int streamIndex);

        int RescaleTs(const EyerAVRational & _codecTimebase, const EyerAVRational & _streamTimebase);

        int GetSize();
        uint8_t * GetDatePtr();

        int GetSideSize();
        uint8_t * GetSideDatePtr();

        double GetSecPTS();

    public:
        EyerAVPacketPrivate * piml = nullptr;
    };
}

#endif //EYERLIB_EYERAVPACKET_HPP
