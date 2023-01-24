#include "EyerAVChannelLayout.hpp"

#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    EyerAVChannelLayout EyerAVChannelLayout::UNKNOW                                 (-1, -1, "UNKNOW", "UNKNOW");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_KEEP_SAME                         (-2, -2, "EYER_KEEP_SAME", "EYER_KEEP_SAME");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_MONO                 (0,     AV_CH_LAYOUT_MONO, "AV_CH_LAYOUT_MONO", "MONO");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_STEREO               (1,     AV_CH_LAYOUT_STEREO, "AV_CH_LAYOUT_STEREO", "STEREO");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_2POINT1              (2,     AV_CH_LAYOUT_2POINT1, "AV_CH_LAYOUT_2POINT1", "2POINT1");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_2_1                  (3,     AV_CH_LAYOUT_2_1, "AV_CH_LAYOUT_2_1", "2_1");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_SURROUND             (4,     AV_CH_LAYOUT_SURROUND, "AV_CH_LAYOUT_SURROUND", "SURROUND");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_3POINT1              (5,     AV_CH_LAYOUT_3POINT1, "AV_CH_LAYOUT_3POINT1", "3POINT1");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_4POINT0              (6,     AV_CH_LAYOUT_4POINT0, "AV_CH_LAYOUT_4POINT0", "4POINT0");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_4POINT1              (7,     AV_CH_LAYOUT_4POINT1, "AV_CH_LAYOUT_4POINT1", "4POINT1");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_2_2                  (8,     AV_CH_LAYOUT_2_2, "AV_CH_LAYOUT_2_2", "2_2");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_QUAD                 (9,     AV_CH_LAYOUT_QUAD, "AV_CH_LAYOUT_QUAD", "QUAD");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_5POINT0              (10,    AV_CH_LAYOUT_5POINT0, "AV_CH_LAYOUT_5POINT0", "5POINT0");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_5POINT1              (11,    AV_CH_LAYOUT_5POINT1, "AV_CH_LAYOUT_5POINT1", "5POINT1");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_5POINT0_BACK         (12,    AV_CH_LAYOUT_5POINT0_BACK, "AV_CH_LAYOUT_5POINT0_BACK", "5POINT0_BACK");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_5POINT1_BACK         (13,    AV_CH_LAYOUT_5POINT1_BACK, "AV_CH_LAYOUT_5POINT1_BACK", "5POINT1_BACK");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_6POINT0              (14,    AV_CH_LAYOUT_6POINT0, "AV_CH_LAYOUT_6POINT0", "6POINT0");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_6POINT0_FRONT        (15,    AV_CH_LAYOUT_6POINT0_FRONT, "AV_CH_LAYOUT_6POINT0_FRONT", "6POINT0_FRONT");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_HEXAGONAL            (16,    AV_CH_LAYOUT_HEXAGONAL, "AV_CH_LAYOUT_HEXAGONAL", "HEXAGONAL");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_6POINT1              (17,    AV_CH_LAYOUT_6POINT1, "AV_CH_LAYOUT_6POINT1", "6POINT1");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_6POINT1_BACK         (18,    AV_CH_LAYOUT_6POINT1_BACK, "AV_CH_LAYOUT_6POINT1_BACK", "6POINT1_BACK");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_6POINT1_FRONT        (19,    AV_CH_LAYOUT_6POINT1_FRONT, "AV_CH_LAYOUT_6POINT1_FRONT", "6POINT1_FRONT");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_7POINT0              (20,    AV_CH_LAYOUT_7POINT0, "AV_CH_LAYOUT_7POINT0", "7POINT0");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_7POINT0_FRONT        (21,    AV_CH_LAYOUT_7POINT0_FRONT, "AV_CH_LAYOUT_7POINT0_FRONT", "7POINT0_FRONT");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_7POINT1              (22,    AV_CH_LAYOUT_7POINT1, "AV_CH_LAYOUT_7POINT1", "7POINT1");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_7POINT1_WIDE         (23,    AV_CH_LAYOUT_7POINT1_WIDE, "AV_CH_LAYOUT_7POINT1_WIDE", "7POINT1_WIDE");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_7POINT1_WIDE_BACK    (24,    AV_CH_LAYOUT_7POINT1_WIDE_BACK, "AV_CH_LAYOUT_7POINT1_WIDE_BACK", "7POINT1_WIDE_BACK");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_OCTAGONAL            (25,    AV_CH_LAYOUT_OCTAGONAL, "AV_CH_LAYOUT_OCTAGONAL", "OCTAGONAL");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_HEXADECAGONAL        (26,    AV_CH_LAYOUT_HEXADECAGONAL, "AV_CH_LAYOUT_HEXADECAGONAL", "HEXADECAGONAL");
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_STEREO_DOWNMIX       (27,    AV_CH_LAYOUT_STEREO_DOWNMIX, "AV_CH_LAYOUT_STEREO_DOWNMIX", "STEREO_DOWNMIX");
    // EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_22POINT2             (28,    AV_CH_LAYOUT_22POINT2);

    EyerAVChannelLayout::EyerAVChannelLayout()
       : EyerAVChannelLayout(0, AV_CH_LAYOUT_MONO, "AV_CH_LAYOUT_MONO", "MONO")
    {

    }

    EyerAVChannelLayout::EyerAVChannelLayout(int _id, uint64_t _ffmpegId, const EyerString & _name, const EyerString & _descname)
    {
        id          = _id;
        ffmpegId    = _ffmpegId;
        name        = _name;
        descName    = _descname;
    }

    EyerAVChannelLayout::EyerAVChannelLayout(const EyerAVChannelLayout & channelLayout)
    {
        *this = channelLayout;
    }

    EyerAVChannelLayout & EyerAVChannelLayout::operator = (const EyerAVChannelLayout & channelLayout)
    {
        id          = channelLayout.id;
        ffmpegId    = channelLayout.ffmpegId;
        name        = channelLayout.name;
        descName    = channelLayout.descName;
        return *this;
    }

    const bool EyerAVChannelLayout::operator == (const EyerAVChannelLayout & format) const
    {
        return id == format.id;
    }

    const bool EyerAVChannelLayout::operator != (const EyerAVChannelLayout & format) const
    {
        return id != format.id;
    }

    EyerAVChannelLayout EyerAVChannelLayout::GetById(int id)
    {
        if(id == EYER_AV_CH_LAYOUT_MONO.id){
            return EYER_AV_CH_LAYOUT_MONO;
        }
        else if(id == EYER_AV_CH_LAYOUT_STEREO.id){
            return EYER_AV_CH_LAYOUT_STEREO;
        }
        else if(id == EYER_AV_CH_LAYOUT_2POINT1.id){
            return EYER_AV_CH_LAYOUT_2POINT1;
        }
        else if(id == EYER_AV_CH_LAYOUT_2_1.id){
            return EYER_AV_CH_LAYOUT_2_1;
        }
        else if(id == EYER_AV_CH_LAYOUT_SURROUND.id){
            return EYER_AV_CH_LAYOUT_SURROUND;
        }
        else if(id == EYER_AV_CH_LAYOUT_3POINT1.id){
            return EYER_AV_CH_LAYOUT_3POINT1;
        }
        else if(id == EYER_AV_CH_LAYOUT_4POINT0.id){
            return EYER_AV_CH_LAYOUT_4POINT0;
        }
        else if(id == EYER_AV_CH_LAYOUT_4POINT1.id){
            return EYER_AV_CH_LAYOUT_4POINT1;
        }
        else if(id == EYER_AV_CH_LAYOUT_2_2.id){
            return EYER_AV_CH_LAYOUT_2_2;
        }
        else if(id == EYER_AV_CH_LAYOUT_QUAD.id){
            return EYER_AV_CH_LAYOUT_QUAD;
        }
        else if(id == EYER_AV_CH_LAYOUT_5POINT0.id){
            return EYER_AV_CH_LAYOUT_5POINT0;
        }
        else if(id == EYER_AV_CH_LAYOUT_5POINT1.id){
            return EYER_AV_CH_LAYOUT_5POINT1;
        }
        else if(id == EYER_AV_CH_LAYOUT_5POINT0_BACK.id){
            return EYER_AV_CH_LAYOUT_5POINT0_BACK;
        }
        else if(id == EYER_AV_CH_LAYOUT_5POINT1_BACK.id){
            return EYER_AV_CH_LAYOUT_5POINT1_BACK;
        }
        else if(id == EYER_AV_CH_LAYOUT_6POINT0.id){
            return EYER_AV_CH_LAYOUT_6POINT0;
        }
        else if(id == EYER_AV_CH_LAYOUT_6POINT0_FRONT.id){
            return EYER_AV_CH_LAYOUT_6POINT0_FRONT;
        }
        else if(id == EYER_AV_CH_LAYOUT_HEXAGONAL.id){
            return EYER_AV_CH_LAYOUT_HEXAGONAL;
        }
        else if(id == EYER_AV_CH_LAYOUT_6POINT1.id){
            return EYER_AV_CH_LAYOUT_6POINT1;
        }
        else if(id == EYER_AV_CH_LAYOUT_6POINT1_BACK.id){
            return EYER_AV_CH_LAYOUT_6POINT1_BACK;
        }
        else if(id == EYER_AV_CH_LAYOUT_6POINT1_FRONT.id){
            return EYER_AV_CH_LAYOUT_6POINT1_FRONT;
        }
        else if(id == EYER_AV_CH_LAYOUT_7POINT0.id){
            return EYER_AV_CH_LAYOUT_7POINT0;
        }
        else if(id == EYER_AV_CH_LAYOUT_7POINT0_FRONT.id){
            return EYER_AV_CH_LAYOUT_7POINT0_FRONT;
        }
        else if(id == EYER_AV_CH_LAYOUT_7POINT1.id){
            return EYER_AV_CH_LAYOUT_7POINT1;
        }
        else if(id == EYER_AV_CH_LAYOUT_7POINT1_WIDE.id){
            return EYER_AV_CH_LAYOUT_7POINT1_WIDE;
        }
        else if(id == EYER_AV_CH_LAYOUT_7POINT1_WIDE_BACK.id){
            return EYER_AV_CH_LAYOUT_7POINT1_WIDE_BACK;
        }
        else if(id == EYER_AV_CH_LAYOUT_OCTAGONAL.id){
            return EYER_AV_CH_LAYOUT_OCTAGONAL;
        }
        else if(id == EYER_AV_CH_LAYOUT_HEXADECAGONAL.id){
            return EYER_AV_CH_LAYOUT_HEXADECAGONAL;
        }
        else if(id == EYER_AV_CH_LAYOUT_STEREO_DOWNMIX.id){
            return EYER_AV_CH_LAYOUT_STEREO_DOWNMIX;
        }

        else if(id == EYER_KEEP_SAME.id){
            return EYER_KEEP_SAME;
        }

        return UNKNOW;
    }

    EyerAVChannelLayout EyerAVChannelLayout::GetByFFmpegId(uint64_t ffmpegId)
    {
        if(ffmpegId == AV_CH_LAYOUT_MONO){
            return EYER_AV_CH_LAYOUT_MONO;
        }
        else if(ffmpegId == AV_CH_LAYOUT_STEREO){
            return EYER_AV_CH_LAYOUT_STEREO;
        }
        else if(ffmpegId == AV_CH_LAYOUT_2POINT1){
            return EYER_AV_CH_LAYOUT_2POINT1;
        }
        else if(ffmpegId == AV_CH_LAYOUT_2_1){
            return EYER_AV_CH_LAYOUT_2_1;
        }
        else if(ffmpegId == AV_CH_LAYOUT_SURROUND){
            return EYER_AV_CH_LAYOUT_SURROUND;
        }
        else if(ffmpegId == AV_CH_LAYOUT_3POINT1){
            return EYER_AV_CH_LAYOUT_3POINT1;
        }
        else if(ffmpegId == AV_CH_LAYOUT_4POINT0){
            return EYER_AV_CH_LAYOUT_4POINT0;
        }
        else if(ffmpegId == AV_CH_LAYOUT_4POINT1){
            return EYER_AV_CH_LAYOUT_4POINT1;
        }
        else if(ffmpegId == AV_CH_LAYOUT_2_2){
            return EYER_AV_CH_LAYOUT_2_2;
        }
        else if(ffmpegId == AV_CH_LAYOUT_QUAD){
            return EYER_AV_CH_LAYOUT_QUAD;
        }
        else if(ffmpegId == AV_CH_LAYOUT_5POINT0){
            return EYER_AV_CH_LAYOUT_5POINT0;
        }
        else if(ffmpegId == AV_CH_LAYOUT_5POINT1){
            return EYER_AV_CH_LAYOUT_5POINT1;
        }
        else if(ffmpegId == AV_CH_LAYOUT_5POINT0_BACK){
            return EYER_AV_CH_LAYOUT_5POINT0_BACK;
        }
        else if(ffmpegId == AV_CH_LAYOUT_5POINT1_BACK){
            return EYER_AV_CH_LAYOUT_5POINT1_BACK;
        }
        else if(ffmpegId == AV_CH_LAYOUT_6POINT0){
            return EYER_AV_CH_LAYOUT_6POINT0;
        }
        else if(ffmpegId == AV_CH_LAYOUT_6POINT0_FRONT){
            return EYER_AV_CH_LAYOUT_6POINT0_FRONT;
        }
        else if(ffmpegId == AV_CH_LAYOUT_HEXAGONAL){
            return EYER_AV_CH_LAYOUT_HEXAGONAL;
        }
        else if(ffmpegId == AV_CH_LAYOUT_6POINT1){
            return EYER_AV_CH_LAYOUT_6POINT1;
        }
        else if(ffmpegId == AV_CH_LAYOUT_6POINT1_BACK){
            return EYER_AV_CH_LAYOUT_6POINT1_BACK;
        }
        else if(ffmpegId == AV_CH_LAYOUT_6POINT1_FRONT){
            return EYER_AV_CH_LAYOUT_6POINT1_FRONT;
        }
        else if(ffmpegId == AV_CH_LAYOUT_7POINT0){
            return EYER_AV_CH_LAYOUT_7POINT0;
        }
        else if(ffmpegId == AV_CH_LAYOUT_7POINT0_FRONT){
            return EYER_AV_CH_LAYOUT_7POINT0_FRONT;
        }
        else if(ffmpegId == AV_CH_LAYOUT_7POINT1){
            return EYER_AV_CH_LAYOUT_7POINT1;
        }
        else if(ffmpegId == AV_CH_LAYOUT_7POINT1_WIDE){
            return EYER_AV_CH_LAYOUT_7POINT1_WIDE;
        }
        else if(ffmpegId == AV_CH_LAYOUT_7POINT1_WIDE_BACK){
            return EYER_AV_CH_LAYOUT_7POINT1_WIDE_BACK;
        }
        else if(ffmpegId == AV_CH_LAYOUT_OCTAGONAL){
            return EYER_AV_CH_LAYOUT_OCTAGONAL;
        }
        else if(ffmpegId == AV_CH_LAYOUT_HEXADECAGONAL){
            return EYER_AV_CH_LAYOUT_HEXADECAGONAL;
        }
        else if(ffmpegId == AV_CH_LAYOUT_STEREO_DOWNMIX){
            return EYER_AV_CH_LAYOUT_STEREO_DOWNMIX;
        }
        /*
        else if(ffmpegId == AV_CH_LAYOUT_22POINT2){
            return EYER_AV_CH_LAYOUT_22POINT2;
        }
         */

        return UNKNOW;
    }

    std::vector<EyerAVChannelLayout> EyerAVChannelLayout::ListAllAVChannelLayout()
    {
        std::vector<EyerAVChannelLayout> list;
        list.push_back(EYER_AV_CH_LAYOUT_MONO);
        list.push_back(EYER_AV_CH_LAYOUT_STEREO);
        list.push_back(EYER_AV_CH_LAYOUT_2POINT1);
        list.push_back(EYER_AV_CH_LAYOUT_2_1);
        list.push_back(EYER_AV_CH_LAYOUT_SURROUND);
        list.push_back(EYER_AV_CH_LAYOUT_3POINT1);
        list.push_back(EYER_AV_CH_LAYOUT_4POINT0);
        list.push_back(EYER_AV_CH_LAYOUT_4POINT1);
        list.push_back(EYER_AV_CH_LAYOUT_2_2);
        list.push_back(EYER_AV_CH_LAYOUT_QUAD);
        list.push_back(EYER_AV_CH_LAYOUT_5POINT0);
        list.push_back(EYER_AV_CH_LAYOUT_5POINT1);
        list.push_back(EYER_AV_CH_LAYOUT_5POINT0_BACK);
        list.push_back(EYER_AV_CH_LAYOUT_5POINT1_BACK);
        list.push_back(EYER_AV_CH_LAYOUT_6POINT0);
        list.push_back(EYER_AV_CH_LAYOUT_6POINT0_FRONT);
        list.push_back(EYER_AV_CH_LAYOUT_HEXAGONAL);
        list.push_back(EYER_AV_CH_LAYOUT_6POINT1);
        list.push_back(EYER_AV_CH_LAYOUT_6POINT1_BACK);
        list.push_back(EYER_AV_CH_LAYOUT_6POINT1_FRONT);
        list.push_back(EYER_AV_CH_LAYOUT_7POINT0);
        list.push_back(EYER_AV_CH_LAYOUT_7POINT0_FRONT);
        list.push_back(EYER_AV_CH_LAYOUT_7POINT1);
        list.push_back(EYER_AV_CH_LAYOUT_7POINT1_WIDE);
        list.push_back(EYER_AV_CH_LAYOUT_7POINT1_WIDE_BACK);
        list.push_back(EYER_AV_CH_LAYOUT_OCTAGONAL);
        list.push_back(EYER_AV_CH_LAYOUT_HEXADECAGONAL);
        list.push_back(EYER_AV_CH_LAYOUT_STEREO_DOWNMIX);

        return list;
    }

    int EyerAVChannelLayout::GetChannelLayoutNBChannels(const EyerAVChannelLayout & channelLayout)
    {
        return av_get_channel_layout_nb_channels(channelLayout.ffmpegId);
    }

    EyerAVChannelLayout EyerAVChannelLayout::GetDefaultChannelLayout(int channel)
    {
        return GetByFFmpegId(av_get_default_channel_layout(channel));
    }

    const EyerString EyerAVChannelLayout::GetName() const
    {
        return name;
    }

    const EyerString EyerAVChannelLayout::GetDescName() const
    {
        return descName;
    }

    const int EyerAVChannelLayout::GetId() const
    {
        return id;
    }

    const int EyerAVChannelLayout::GetFFmpegId() const
    {
        return ffmpegId;
    }
}