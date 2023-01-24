#ifndef EYERLIB_MATRIXTRANSPOSE_HPP
#define EYERLIB_MATRIXTRANSPOSE_HPP

#include <gtest/gtest.h>
#include "EyerMath/Eath.hpp"

TEST(EyerMath, Matrix4x4_Transpose)
{
    EyerLog("===================Matrix4x4_Transpose===================\n");

    Eyer::Eatrix<float> mat(10, 10);
    mat.Set(0, 9, 1.0);
    mat.PrintInfo();

    ASSERT_EQ(mat.Get(0, 9), 1.0);
    ASSERT_EQ(mat.Get(9, 0), 0.0);

    Eyer::Eatrix<float> res = mat.Transpose();

    ASSERT_EQ(mat.Get(0, 9), 1.0);
    ASSERT_EQ(mat.Get(9, 0), 0.0);

    ASSERT_EQ(res.Get(0, 9), 0.0);
    ASSERT_EQ(res.Get(9, 0), 1.0);

    mat.TransposeSelf();

    ASSERT_EQ(mat.Get(0, 9), 0.0);
    ASSERT_EQ(mat.Get(9, 0), 1.0);

    EyerLog("===================Matrix4x4_Transpose===================\n");



}


#endif //EYERLIB_MATRIXTRANSPOSE_HPP
