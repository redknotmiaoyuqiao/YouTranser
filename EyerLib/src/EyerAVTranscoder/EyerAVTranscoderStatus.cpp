#include "EyerAVTranscoderStatus.hpp"

namespace Eyer
{
    EyerAVTranscoderStatus EyerAVTranscoderStatus::PREPARE  (1, "PREPARE");
    EyerAVTranscoderStatus EyerAVTranscoderStatus::ING      (2, "ING");
    EyerAVTranscoderStatus EyerAVTranscoderStatus::FAIL     (3, "FAIL");
    EyerAVTranscoderStatus EyerAVTranscoderStatus::SUCC     (4, "SUCC");

    EyerAVTranscoderStatus::EyerAVTranscoderStatus()
    {

    }

    EyerAVTranscoderStatus::EyerAVTranscoderStatus(int _id, const EyerString & _name)
        : id(_id)
        , name(_name)
    {
    }

    EyerAVTranscoderStatus::~EyerAVTranscoderStatus()
    {

    }

    EyerAVTranscoderStatus::EyerAVTranscoderStatus(const EyerAVTranscoderStatus & status)
    {
        *this = status;
    }

    EyerAVTranscoderStatus & EyerAVTranscoderStatus::operator = (const EyerAVTranscoderStatus & status)
    {
        id = status.id;
        name = status.name;
        return *this;
    }

    bool EyerAVTranscoderStatus::operator == (const EyerAVTranscoderStatus & status) const
    {
        return id == status.id;
    }

    bool EyerAVTranscoderStatus::operator != (const EyerAVTranscoderStatus & status) const
    {
        return id != status.id;
    }

    const EyerString & EyerAVTranscoderStatus::GetName()
    {
        return name;
    }

    int EyerAVTranscoderStatus::GetId()
    {
        return id;
    }
}