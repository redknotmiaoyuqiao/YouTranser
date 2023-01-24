#include "EyerAVRational.hpp"

#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    EyerAVRational::EyerAVRational()
    {

    }

    EyerAVRational::EyerAVRational(int _num, int _den)
    {
        num = _num;
        den = _den;
    }

    EyerAVRational::~EyerAVRational()
    {

    }

    EyerAVRational::EyerAVRational(const EyerAVRational & rational)
    {
        *this = rational;
    }

    EyerAVRational & EyerAVRational::operator = (const EyerAVRational & rational)
    {
        num = rational.num;
        den = rational.den;
        return *this;
    }

    int64_t EyerAVRational::RescaleQ(int64_t a, const EyerAVRational & in, const EyerAVRational & out)
    {
        AVRational i;
        i.den = in.den;
        i.num = in.num;

        AVRational o;
        o.den = out.den;
        o.num = out.den;

        return av_rescale_q(a, i, o);
    }
}