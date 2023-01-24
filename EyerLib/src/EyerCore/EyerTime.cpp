#include "EyerTime.hpp"

#include <time.h>
#include <stdio.h>
#include <chrono>
#include <thread>

namespace Eyer
{
    long long EyerTime::GetTime()
    {
        std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	    auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
	    return (long long)tmp.count();
    }

    EyerString EyerTime::TimeFormat()
    {
        char now[64];
#ifdef _MSC_VER

#else
        time_t tt;
        struct tm *ttime;

        time(&tt);

        ttime = localtime(&tt);
        strftime(now,64,"%Y-%m-%d %H:%M:%S",ttime);
#endif // _MSC_VER

        return EyerString(now);
    }

    int EyerTime::EyerSleepMilliseconds(int time)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
        return 0;
    }

    long long EyerTime::GetTimeNano()
    {
        std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> tp = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());
        auto tmp = std::chrono::duration_cast<std::chrono::nanoseconds>(tp.time_since_epoch());
        return (long long)tmp.count();
    }
}