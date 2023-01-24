#include "EyerAVADTS.hpp"

namespace Eyer
{
    EyerAVADTS::EyerAVADTS(EyerBuffer & buffer)
        : EyerAVADTS(buffer.GetPtr(), buffer.GetLen())
    {

    }

    EyerAVADTS::EyerAVADTS(uint8_t * buf, int bufLen)
    {
        buffer.Append(buf, bufLen);

        if(bufLen < 7){
            return;
        }

        EyerBitStream bitStream(buffer);

        // adts_fixed_header();
        syncword                    = bitStream.bs_read_u(12);
        ID                          = bitStream.bs_read_u(1);
        layer                       = bitStream.bs_read_u(2);
        protection_absent           = bitStream.bs_read_u(1);
        profile                     = bitStream.bs_read_u(2);
        sampling_frequency_index    = bitStream.bs_read_u(4);
        private_bit                 = bitStream.bs_read_u(1);
        channel_configuration       = bitStream.bs_read_u(3);
        original_copy               = bitStream.bs_read_u(1);
        home                        = bitStream.bs_read_u(1);

        // adts_variable_header();
        copyright_identification_bit        = bitStream.bs_read_u(1);
        copyright_identification_start      = bitStream.bs_read_u(1);
        aac_frame_length                    = bitStream.bs_read_u(13);
        adts_buffer_fullness                = bitStream.bs_read_u(11);
        number_of_raw_data_blocks_in_frame  = bitStream.bs_read_u(2);


        EyerLog("syncword: %d\n", syncword);
        EyerLog("ID: %d\n", ID);
        EyerLog("layer: %d\n", layer);
        EyerLog("protection_absent: %d\n", protection_absent);
        EyerLog("profile: %d\n", profile);
        EyerLog("sampling_frequency_index: %d\n", sampling_frequency_index);
        EyerLog("private_bit: %d\n", private_bit);
        EyerLog("channel_configuration: %d\n", channel_configuration);
        EyerLog("original_copy: %d\n", original_copy);
        EyerLog("home: %d\n", home);

        EyerLog("aac_frame_length: %d\n", aac_frame_length);
        EyerLog("adts_buffer_fullness: %d\n", adts_buffer_fullness);
        EyerLog("number_of_raw_data_blocks_in_frame: %d\n", number_of_raw_data_blocks_in_frame);

    }

    EyerAVADTS::~EyerAVADTS()
    {

    }
}