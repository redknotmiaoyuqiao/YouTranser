#include "EyerAVTranscoderError.hpp"

namespace Eyer
{
    EyerAVTranscoderError EyerAVTranscoderError::OPEN_INPUT_FAIL            (-1, "OPEN_INPUT_FAIL");
    EyerAVTranscoderError EyerAVTranscoderError::OPEN_OUTPUT_FAIL           (-2, "OPEN_OUTPUT_FAIL");
    EyerAVTranscoderError EyerAVTranscoderError::OPEN_WRITE_HEAD_FAIL       (-3, "OPEN_WRITE_HEAD_FAIL");
    EyerAVTranscoderError EyerAVTranscoderError::INTERRUPT_FAIL             (-4, "INTERRUPT_FAIL");
    EyerAVTranscoderError EyerAVTranscoderError::INIT_ENCODER_FAIL          (-5, "INIT_ENCODER_FAIL");

    EyerAVTranscoderError::EyerAVTranscoderError()
    {

    }

    EyerAVTranscoderError::EyerAVTranscoderError(const EyerAVTranscoderError & error)
    {
        *this = error;
    }

    EyerAVTranscoderError::EyerAVTranscoderError(int _code, const EyerString & _desc)
    {
        code = _code;
        desc = _desc;
    }

    EyerAVTranscoderError::~EyerAVTranscoderError()
    {

    }

    EyerAVTranscoderError & EyerAVTranscoderError::operator = (const EyerAVTranscoderError & error)
    {
        code = error.code;
        desc = error.desc;
        return *this;
    }

    int EyerAVTranscoderError::GetCode()
    {
        return code;
    }

    EyerString EyerAVTranscoderError::GetDesc()
    {
        return desc;
    }
}