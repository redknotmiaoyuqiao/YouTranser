#ifndef EYERLIB_EYERAVRATIONAL_HPP
#define EYERLIB_EYERAVRATIONAL_HPP

#include <stdint.h>

namespace Eyer
{
    class EyerAVRational {
    public:
        EyerAVRational();
        EyerAVRational(int _num, int _den);
        ~EyerAVRational();

        EyerAVRational(const EyerAVRational & rational);
        EyerAVRational & operator = (const EyerAVRational & rational);

        static int64_t RescaleQ(int64_t a, const EyerAVRational & in, const EyerAVRational & out);

    public:
        int num = 0;
        int den = 0;
    };
}

#endif //EYERLIB_EYERAVRATIONAL_HPP
