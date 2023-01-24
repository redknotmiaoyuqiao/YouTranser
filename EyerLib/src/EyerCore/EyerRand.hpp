#ifndef EYERLIB_EYERRAND_HPP
#define EYERLIB_EYERRAND_HPP

#include "EyerString.hpp"

namespace Eyer
{
    class EyerRand
    {
    public:
        static int Rand(int x);
        static EyerString RandNumberStr(int length);
    };
}

#endif //EYERLIB_EYERRAND_HPP
