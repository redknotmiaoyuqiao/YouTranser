#ifndef EYERLIB_EYERAVADTS_HPP
#define EYERLIB_EYERAVADTS_HPP

#include <stdint.h>
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerAVADTS {
    public:
        EyerAVADTS(EyerBuffer & buffer);
        EyerAVADTS(uint8_t * buf, int bufLen);
        ~EyerAVADTS();

        EyerBuffer buffer;

        uint32_t syncword = 0;
        uint32_t ID = 0;
        uint32_t layer = 0;
        uint32_t protection_absent = 0;
        uint32_t profile = 0;
        uint32_t sampling_frequency_index = 0;
        uint32_t private_bit = 0;
        uint32_t channel_configuration = 0;
        uint32_t original_copy = 0;
        uint32_t home = 0;
        uint32_t copyright_identification_bit = 0;
        uint32_t copyright_identification_start = 0;
        uint32_t aac_frame_length = 0;
        uint32_t adts_buffer_fullness = 0;
        uint32_t number_of_raw_data_blocks_in_frame = 0;
    };
}



#endif //EYERLIB_EYERAVADTS_HPP
