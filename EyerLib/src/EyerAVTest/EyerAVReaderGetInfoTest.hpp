#ifndef EYERLIB_EYERAVREADERGETINFOTEST_HPP
#define EYERLIB_EYERAVREADERGETINFOTEST_HPP

#include <gtest/gtest.h>
#include "EyerAV/EyerAV.hpp"

TEST(EyerAV, EyerAVReaderGetInfoTest)
{
    Eyer::EyerAVReader reader("./demo.mp4");
}

#endif //EYERLIB_EYERAVREADERGETINFOTEST_HPP
