#ifndef	EYER_CORE_TIME_H
#define	EYER_CORE_TIME_H

#include "EyerString.hpp"

namespace Eyer
{
    class EyerTime
    {
    public:
        static long long GetTimeNano();
        static long long GetTime();
        static int EyerSleepMilliseconds(int time);
        static EyerString Milliseconds_to_time(int milliseconds);
    };
}

#endif
