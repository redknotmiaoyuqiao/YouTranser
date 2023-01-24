#include "BLOCK_TIME.hpp"
#include "EyerTime.hpp"
#include "EyerLog.hpp"

namespace Eyer
{
    BLOCK_TIME::BLOCK_TIME(const char * _blockName)
    {
        blockName = _blockName;
        startTime = Eyer::EyerTime::GetTime();
    }

    BLOCK_TIME::BLOCK_TIME(EyerString & _blockName)
    {
        blockName = _blockName;
        startTime = Eyer::EyerTime::GetTime();
    }

    BLOCK_TIME::~BLOCK_TIME()
    {
        endTime = Eyer::EyerTime::GetTime();
        long long duration = endTime - startTime;

        EyerLog("%s = %lldms\n", blockName.c_str(), duration);
    }
}