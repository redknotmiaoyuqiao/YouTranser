#include "EyerTime.hpp"

#include <time.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <iomanip>
#include <sstream>


namespace Eyer
{
    long long EyerTime::GetTime()
    {
        std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	    auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
	    return (long long)tmp.count();
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

    EyerString EyerTime::Milliseconds_to_time(int milliseconds)
    {
        int hours = milliseconds / (1000 * 60 * 60);
        int minutes = (milliseconds % (1000 * 60 * 60)) / (1000 * 60);
        int seconds = (milliseconds % (1000 * 60)) / 1000;
        int milliseconds_remainder = milliseconds % 1000;

        std::ostringstream ss;
        ss << std::setw(2) << std::setfill('0') << hours << ":"
           << std::setw(2) << std::setfill('0') << minutes << ":"
           << std::setw(2) << std::setfill('0') << seconds << ","
           << std::setw(3) << std::setfill('0') << milliseconds_remainder;

        return EyerString(ss.str());
    }

}