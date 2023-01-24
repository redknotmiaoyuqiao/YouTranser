#ifndef EYERLIB_MATHCROPTEST_HPP
#define EYERLIB_MATHCROPTEST_HPP

#include <gtest/gtest.h>
#include "EyerMath/EyerMath.hpp"

TEST(EyerMath, CropTest_FIT_XY)
{
    Eyer::Eyer2DCrop crop(1920, 1080);
    crop.Crop(100, 100, Eyer::EyerCropType::FIT_CENTER);

    Eyer::Eatrix4x4<float> ortho;
    ortho.SetOrtho(-100, 100, -100, 100, 0, 100);
}

#endif //EYERLIB_MATHCROPTEST_HPP
