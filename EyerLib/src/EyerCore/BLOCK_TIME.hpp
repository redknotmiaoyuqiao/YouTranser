#ifndef EYERLIB_BLOCK_TIME_HPP
#define EYERLIB_BLOCK_TIME_HPP

#include "EyerString.hpp"
#include "EyerTime.hpp"
#include "EyerLog.hpp"

namespace Eyer
{
    class BLOCK_TIME {
    public:
        inline BLOCK_TIME(const char * _blockName)
        {
            blockName = _blockName;
            startTime = Eyer::EyerTime::GetTime();
        }

        inline BLOCK_TIME(EyerString & _blockName)
        {
            blockName = _blockName;
            startTime = Eyer::EyerTime::GetTime();
        }

        inline ~BLOCK_TIME()
        {
            endTime = Eyer::EyerTime::GetTime();
            long long duration = endTime - startTime;
            EyerLog("%s = %lld ms\n", blockName.c_str(), duration);
        }

    private:
        EyerString blockName;
        long long startTime = 0;
        long long endTime = 0;
    };
}



#endif //EYERLIB_BLOCK_TIME_HPP
