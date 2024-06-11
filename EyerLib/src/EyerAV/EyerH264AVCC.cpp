#include "EyerH264AVCC.hpp"

namespace Eyer
{
    EyerH264AVCC::EyerH264AVCC(const EyerBuffer & _avcc)
    {
        avcc = _avcc;
        EyerBitStream bitStream(avcc);

        int version                 = bitStream.bs_read_u8();
        int avc_profile             = bitStream.bs_read_u8();
        int avc_compatibility       = bitStream.bs_read_u8();
        int avc_level               = bitStream.bs_read_u8();

        int reserved                = bitStream.bs_read_u(6);
        NALULengthSizeMinusOne      = bitStream.bs_read_u(2);

        reserved                    = bitStream.bs_read_u(3);
        int number_of_SPS_NALUs     = bitStream.bs_read_u(5);

        for(int i=0; i<number_of_SPS_NALUs; i++){
            int SPS_size = bitStream.bs_read_u(16);

            sps.Clear();
            sps.Append(bitStream.p, SPS_size);

            for(int j=0;j<SPS_size;j++){
                bitStream.bs_read_u8();
            }
        }


        int number_of_PPS_NALUs     = bitStream.bs_read_u(8);
        for(int i=0; i<number_of_PPS_NALUs; i++){
            int PPS_size = bitStream.bs_read_u(16);

            pps.Clear();
            pps.Append(bitStream.p, PPS_size);

            for(int j=0;j<PPS_size;j++){
                bitStream.bs_read_u8();
            }
        }
    }

    EyerH264AVCC::~EyerH264AVCC()
    {

    }

    EyerBuffer EyerH264AVCC::GetSPS()
    {
        return sps;
    }

    EyerBuffer EyerH264AVCC::GetPPS()
    {
        return pps;
    }

    int EyerH264AVCC::GetNALULengthSizeMinusOne()
    {
        return NALULengthSizeMinusOne;
    }
}