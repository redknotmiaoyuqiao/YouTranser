#ifndef EYERLIB_EYERAVBITSTREAMFILTER_HPP
#define EYERLIB_EYERAVBITSTREAMFILTER_HPP

#include "EyerAVBitstreamFilterType.hpp"
#include "EyerAVStream.hpp"
#include "EyerAVPacket.hpp"

namespace Eyer
{
    class EyerAVBitstreamFilterPrivate;

    class EyerAVBitstreamFilter
    {
    public:
        EyerAVBitstreamFilter(const EyerAVBitstreamFilterType & type, const EyerAVStream & avStream);
        ~EyerAVBitstreamFilter();

        int SendPacket(EyerAVPacket & packet);
        int SendPacketNull();
        int RecvPacket(EyerAVPacket & packet);

        static int QueryAllBitstreamFilter();

    private:
        EyerAVBitstreamFilter (const EyerAVBitstreamFilter & filter) = delete;
        EyerAVBitstreamFilter & operator = (const EyerAVBitstreamFilter & filter) = delete;

    public:
        EyerAVBitstreamFilterPrivate * piml = nullptr;
    };
}

#endif //EYERLIB_EYERAVBITSTREAMFILTER_HPP
