#include "EyerAVBitstreamFilter.hpp"

#include "EyerAVFFmpegHeader.hpp"
#include "EyerAVBitstreamFilterPrivate.hpp"
#include "EyerAVStreamPrivate.hpp"
#include "EyerAVPacketPrivate.hpp"

namespace Eyer
{
    int EyerAVBitstreamFilter::QueryAllBitstreamFilter()
    {
        void *state = NULL;

        const AVBitStreamFilter * bsf = nullptr;
        while (1) {
            bsf = av_bsf_next(&state);
            if(bsf == nullptr){
                break;
            }
            EyerLog("%s\n", bsf->name);
        }

        return 0;
    }

    EyerAVBitstreamFilter::EyerAVBitstreamFilter(const EyerAVBitstreamFilterType & type, const EyerAVStream & avStream)
    {
        piml = new EyerAVBitstreamFilterPrivate();

        const AVBitStreamFilter * bsf = av_bsf_get_by_name(type.str.c_str());
        int ret = av_bsf_alloc(bsf, &piml->ctx);

        if(type.id == EyerAVBitstreamFilterType::H264_METADATA.id){
            char * allcontent = (char *)"086f3693b7b34f2c965321492feee5b8+HelloWorld";
            av_opt_set(piml->ctx->priv_data, "sei_user_data", allcontent, AV_OPT_SEARCH_CHILDREN);
        }

        avcodec_parameters_copy(piml->ctx->par_in, avStream.piml->codecpar);
        av_bsf_init(piml->ctx);
    }

    EyerAVBitstreamFilter::~EyerAVBitstreamFilter()
    {
        if(piml->ctx != nullptr){
            av_bsf_free(&piml->ctx);
            piml->ctx = nullptr;
        }
        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    int EyerAVBitstreamFilter::SendPacket(EyerAVPacket & packet)
    {
        return av_bsf_send_packet(piml->ctx, packet.piml->packet);
    }

    int EyerAVBitstreamFilter::SendPacketNull()
    {
        return av_bsf_send_packet(piml->ctx, nullptr);
    }

    int EyerAVBitstreamFilter::RecvPacket(EyerAVPacket & packet)
    {
        return av_bsf_receive_packet(piml->ctx, packet.piml->packet);
    }
}