#ifndef EYERLIB_BLOCK_TIME_HPP
#define EYERLIB_BLOCK_TIME_HPP

#include "EyerString.hpp"

namespace Eyer
{
    class BLOCK_TIME {
    public:
        BLOCK_TIME(const char * _blockName);
        BLOCK_TIME(EyerString & _blockName);
        ~BLOCK_TIME();

    private:
        EyerString blockName;
        long long startTime = 0;
        long long endTime = 0;
    };
}



#endif //EYERLIB_BLOCK_TIME_HPP
