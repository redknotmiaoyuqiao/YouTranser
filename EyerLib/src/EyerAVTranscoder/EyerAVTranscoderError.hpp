#ifndef EYERLIB_EYERAVTRANSCODERERROR_HPP
#define EYERLIB_EYERAVTRANSCODERERROR_HPP

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerAVTranscoderError
    {
    public:
        static EyerAVTranscoderError OPEN_INPUT_FAIL;
        static EyerAVTranscoderError OPEN_OUTPUT_FAIL;
        static EyerAVTranscoderError OPEN_WRITE_HEAD_FAIL;
        static EyerAVTranscoderError INTERRUPT_FAIL;
        static EyerAVTranscoderError INIT_ENCODER_FAIL;

        EyerAVTranscoderError();
        EyerAVTranscoderError(const EyerAVTranscoderError & error);
        EyerAVTranscoderError(int code, const EyerString & _desc);
        ~EyerAVTranscoderError();

        EyerAVTranscoderError & operator = (const EyerAVTranscoderError & error);

        int GetCode();
        EyerString GetDesc();
    private:
        int code;
        EyerString desc;
    };
}

#endif //EYERLIB_EYERAVTRANSCODERERROR_HPP
