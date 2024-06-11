#ifndef EYERLIB_EYERH264AVCC_HPP
#define EYERLIB_EYERH264AVCC_HPP

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerH264AVCC
    {
    public:
        EyerH264AVCC(const EyerBuffer & _avcc);
        ~EyerH264AVCC();

        EyerBuffer GetSPS();
        EyerBuffer GetPPS();

        int GetNALULengthSizeMinusOne();

    private:
        EyerBuffer avcc;

        EyerBuffer sps;
        EyerBuffer pps;

        int NALULengthSizeMinusOne = 0;
    };
}

#endif //EYERLIB_EYERH264AVCC_HPP
