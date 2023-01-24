#ifndef EYERLIB_EYERAVADTSTEST_HPP
#define EYERLIB_EYERAVADTSTEST_HPP

#include <gtest/gtest.h>
#include "EyerAV/EyerAV.hpp"

TEST(EyerAV, EyerAVADTSTest)
{
    uint8_t adtsBuf[] = {255, 241, 80, 128, 47, 159, 252};

    Eyer::EyerAVADTS avadts(adtsBuf, 7);
}

#endif //EYERLIB_EYERAVADTSTEST_HPP
