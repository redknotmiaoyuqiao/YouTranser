#include "EyerAVSampleRate.hpp"

namespace Eyer
{
    EyerAVSampleRate SR_44100(0, 44100);
    EyerAVSampleRate SR_48000(1, 48000);
    EyerAVSampleRate SR_96000(2, 96000);

    EyerAVSampleRate::EyerAVSampleRate(int _id, int _sampleRate)
    {
        id = _id;
        sampleRate = _sampleRate;
    }

    EyerAVSampleRate::EyerAVSampleRate()
    {

    }

    EyerAVSampleRate::EyerAVSampleRate(const EyerAVSampleRate & sampleRate)
    {
        *this = sampleRate;
    }

    EyerAVSampleRate::~EyerAVSampleRate()
    {

    }

    const EyerAVSampleRate & EyerAVSampleRate::operator = (const EyerAVSampleRate & _sampleRate)
    {
        id = _sampleRate.id;
        sampleRate = _sampleRate.sampleRate;
        return *this;
    }

    const bool EyerAVSampleRate::operator == (const EyerAVSampleRate & sampleRate)
    {
        return id == sampleRate.id;
    }

    const bool EyerAVSampleRate::operator != (const EyerAVSampleRate & sampleRate)
    {
        return id != sampleRate.id;
    }

    const int EyerAVSampleRate::GetId() const
    {
        return id;
    }

    const int EyerAVSampleRate::GetSampleRate() const
    {
        return sampleRate;
    }
}