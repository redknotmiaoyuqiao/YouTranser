#ifndef EYERLIB_EYERAVSEIUTILTEST_HPP
#define EYERLIB_EYERAVSEIUTILTEST_HPP

#include <gtest/gtest.h>
#include "EyerAV/EyerAV.hpp"
#include "EyerCore/EyerCore.hpp"

TEST(EyerAV, EyerAVSEIUtilTest)
{
    Eyer::EyerAVSEIUtil avseiUtil;

    unsigned char uuid[] = { 0x54, 0x80, 0x83, 0x97, 0xf0, 0x23, 0x47, 0x4b, 0xb7, 0xf7, 0x4f, 0x32, 0xb5, 0x4e, 0x06, 0xac };
    Eyer::EyerBufferPlus buffer = avseiUtil.GenSEINALU(uuid, 16);

    EyerLog("Buffer: %lld\n", buffer.GetBufferLen());
}

#endif //EYERLIB_EYERAVSEIUTILTEST_HPP
