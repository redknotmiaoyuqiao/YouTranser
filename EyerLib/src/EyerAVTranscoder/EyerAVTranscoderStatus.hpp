#ifndef EYERLIB_EYERAVTRANSCODERSTATUS_HPP
#define EYERLIB_EYERAVTRANSCODERSTATUS_HPP

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerAVTranscoderStatus
    {
    public:
        static EyerAVTranscoderStatus PREPARE;
        static EyerAVTranscoderStatus ING;
        static EyerAVTranscoderStatus FAIL;
        static EyerAVTranscoderStatus SUCC;

        EyerAVTranscoderStatus();
        EyerAVTranscoderStatus(int _id, const EyerString & _name);
        ~EyerAVTranscoderStatus();

        EyerAVTranscoderStatus(const EyerAVTranscoderStatus & status);
        EyerAVTranscoderStatus & operator = (const EyerAVTranscoderStatus & status);

        bool operator == (const EyerAVTranscoderStatus & status) const;
        bool operator != (const EyerAVTranscoderStatus & status) const;

        const EyerString & GetName();
        int GetId();

    private:
        int id;
        EyerString name;
    };
}

#endif //EYERLIB_EYERAVTRANSCODERSTATUS_HPP
