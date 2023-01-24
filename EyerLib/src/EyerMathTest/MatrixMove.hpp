#ifndef EYERLIB_MATRIXMOVE_HPP
#define EYERLIB_MATRIXMOVE_HPP

#include <gtest/gtest.h>
#include "EyerMath/Eath.hpp"

TEST(EyerMath, Matrix4x4_Move_Mul){
    Eyer::Eatrix4x4<float> a;
    Eyer::Eatrix4x4<float> b;
    Eyer::Eatrix4x4<float> c;
    Eyer::Eatrix4x4<float> d;

    EyerLog("========================\n");

    Eyer::Eatrix4x4<float> res_m = a * b * c * d;
}

TEST(EyerMath, Matrix4x4_Move_Sub){
    Eyer::Eatrix4x4<float> a;
    Eyer::Eatrix4x4<float> b;
    Eyer::Eatrix4x4<float> c;
    Eyer::Eatrix4x4<float> d;

    EyerLog("========================\n");

    Eyer::Eatrix4x4<float> res_m = a - b - c - d;
}

#endif //EYERLIB_MATRIXMOVE_HPP
