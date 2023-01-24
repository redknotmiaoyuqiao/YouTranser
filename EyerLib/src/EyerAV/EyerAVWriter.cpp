#include "EyerAVWriter.hpp"

#include "EyerAVPacket.hpp"
#include "EyerAVEncoder.hpp"

#include "EyerAVEncoderPrivate.hpp"
#include "EyerAVWriterPrivate.hpp"
#include "EyerAVPacketPrivate.hpp"

namespace Eyer
{
    EyerAVWriter::EyerAVWriter(const EyerString _path)
    {
        piml = new EyerAVWriterPrivate();
        piml->path = _path;

        /// av_register_all();
        avformat_network_init();

        avformat_alloc_output_context2(&piml->formatCtx, NULL, NULL, piml->path.c_str());
    }

    EyerAVWriter::~EyerAVWriter()
    {
        if(piml->formatCtx != NULL){
            avformat_free_context(piml->formatCtx);
            piml->formatCtx = NULL;
        }
        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    int EyerAVWriter::Open()
    {
        int ret = avio_open(&piml->formatCtx->pb, piml->path.c_str(), AVIO_FLAG_WRITE);
        return ret;
    }

    int EyerAVWriter::Close()
    {
        return avio_close(piml->formatCtx->pb);
    }

    int EyerAVWriter::AddStream(EyerAVEncoder & encoder)
    {

        AVStream * avStream = avformat_new_stream(piml->formatCtx, encoder.piml->codecContext->codec);

        avStream->time_base = encoder.piml->codecContext->time_base;
        avStream->codecpar->codec_tag = 0;
        avcodec_parameters_from_context(avStream->codecpar, encoder.piml->codecContext);

        encoder.piml->codecContext->codec_tag = 0;

        return avStream->index;
    }

    int EyerAVWriter::GetTimebase(EyerAVRational & timebase, int streamIndex)
    {
        timebase.num = piml->formatCtx->streams[streamIndex]->time_base.num;
        timebase.den = piml->formatCtx->streams[streamIndex]->time_base.den;
        return 0;
    }

    EyerAVRational EyerAVWriter::GetTimebase(int streamIndex)
    {
        EyerAVRational timebase;
        GetTimebase(timebase, streamIndex);
        return timebase;
    }

    int EyerAVWriter::WriteHand()
    {
        AVDictionary *dict = NULL;
        // av_dict_set( &dict, "movflags", "faststart", 0 );
        // av_dict_set( &dict, "vtag", "hvc1", 0 );
        int ret = avformat_write_header(piml->formatCtx, &dict);
        av_dict_free(&dict);
        return ret;
    }

    int EyerAVWriter::WriteTrailer()
    {
        int ret = av_write_trailer(piml->formatCtx);
        return ret;
    }

    int EyerAVWriter::WritePacket(EyerAVPacket & packet)
    {
        int ret = av_interleaved_write_frame(piml->formatCtx, packet.piml->packet);
        return ret;
    }
}