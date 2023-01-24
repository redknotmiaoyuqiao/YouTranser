#include "EyerAVPacket.hpp"

#include "EyerAVReaderPrivate.hpp"
#include "EyerAVPacketPrivate.hpp"

namespace Eyer
{
    EyerAVPacket::EyerAVPacket()
    {
        piml = new EyerAVPacketPrivate();
        piml->packet = av_packet_alloc();
    }

    EyerAVPacket::EyerAVPacket(const EyerAVPacket & packet) : EyerAVPacket()
    {
        *this = packet;
    }

    EyerAVPacket::~EyerAVPacket()
    {
        if (piml->packet != nullptr) {
            av_packet_free(&piml->packet);
            piml->packet = nullptr;
        }

        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    EyerAVPacket & EyerAVPacket::operator = (const EyerAVPacket & packet)
    {
        if (piml->packet != nullptr) {
            av_packet_free(&piml->packet);
            piml->packet = nullptr;
        }

        piml->packet = av_packet_clone(packet.piml->packet);
        piml->secPTS = packet.piml->secPTS;

        return *this;
    }

    int64_t EyerAVPacket::GetPTS()
    {
        return piml->packet->pts;
    }

    int EyerAVPacket::GetStreamIndex()
    {
        return piml->packet->stream_index;
    }

    int EyerAVPacket::SetStreamIndex(int streamIndex)
    {
        piml->packet->stream_index = streamIndex;
        return 0;
    }

    int EyerAVPacket::RescaleTs(const EyerAVRational & _codecTimebase, const EyerAVRational & _streamTimebase)
    {
        AVRational codecTimebase;
        codecTimebase.num = _codecTimebase.num;
        codecTimebase.den = _codecTimebase.den;

        AVRational streamTimebase;
        streamTimebase.num = _streamTimebase.num;
        streamTimebase.den = _streamTimebase.den;

        av_packet_rescale_ts(piml->packet, codecTimebase, streamTimebase);

        return 0;
    }

    int EyerAVPacket::GetSize()
    {
        return piml->packet->size;
    }

    uint8_t * EyerAVPacket::GetDatePtr()
    {
        return piml->packet->data;
    }

    int EyerAVPacket::GetSideSize()
    {
        return piml->packet->side_data->size;
    }

    uint8_t * EyerAVPacket::GetSideDatePtr()
    {
        if(AV_PKT_DATA_MATROSKA_BLOCKADDITIONAL == piml->packet->side_data->type)
            EyerLog("piml->packet->side_data->type: %d\n", piml->packet->side_data->type);
        return piml->packet->side_data->data;
    }

    double EyerAVPacket::GetSecPTS()
    {
        return piml->secPTS;
    }
}