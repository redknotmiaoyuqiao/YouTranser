#ifndef EYERLIB_MATRIXCOPY_HPP
#define EYERLIB_MATRIXCOPY_HPP

#include <gtest/gtest.h>
#include "EyerMath/Eath.hpp"

TEST(EyerMath, Matrix4x4_Copy_Transpose)
{
    Eyer::EatrixF4x4 mat;
    mat.SetTrans(3.0, 2.0,5.0);
    // mat.PrintInfo();

    Eyer::EatrixF4x4 mp;

    EyerLog("=============================\n");
    for(int i=0;i<3;i++){
        mp.Transpose(mat);
        // mp.PrintInfo();
    }
    EyerLog("=============================\n");
}

TEST(EyerMath, Matrix4x4_Copy_Add)
{
    Eyer::EatrixF4x4 matA;
    matA.SetTrans(3.0, 2.0,5.0);

    Eyer::EatrixF4x4 matB;
    matB.SetRotato(1.0, 0.0, 0.0, 3.14);

    Eyer::EatrixF4x4 matC;
    matC.SetTrans(3.0, 2.0,5.0);

    Eyer::EatrixF4x4 matD;
    matD.SetTrans(3.0, 2.0,5.0);

    Eyer::EatrixF4x4 mp;

    Eyer::EatrixF4x4 mat = matA * matB * matC;

    EyerLog("=============================\n");
    for(int i=0;i<1;i++){
        mp = mp.Zeros() + matA + matB + matC + matD;
        mp.PrintInfo();

        ASSERT_EQ(mp.Get(0, 0), 4.0); ASSERT_EQ(mp.Get(0, 1), 0.0); ASSERT_EQ(mp.Get(0, 2), 0.0); ASSERT_EQ(mp.Get(0, 3), 12.0);
        ASSERT_EQ(mp.Get(1, 0), 0.0); ASSERT_EQ(mp.Get(1, 1), 4.0); ASSERT_EQ(mp.Get(1, 2), 0.0); ASSERT_EQ(mp.Get(1, 3), 8.0);
        ASSERT_EQ(mp.Get(2, 0), 0.0); ASSERT_EQ(mp.Get(2, 1), 0.0); ASSERT_EQ(mp.Get(2, 2), 4.0); ASSERT_EQ(mp.Get(2, 3), 20.0);
        ASSERT_EQ(mp.Get(3, 0), 0.0); ASSERT_EQ(mp.Get(3, 1), 0.0); ASSERT_EQ(mp.Get(3, 2), 0.0); ASSERT_EQ(mp.Get(3, 3), 4.0);
    }
    EyerLog("=============================\n");
}

TEST(EyerMath, Matrix4x4_Copy_Mul)
{
    Eyer::EatrixF4x4 matA;
    matA.SetTrans(3.0, 2.0,5.0);

    Eyer::EatrixF4x4 matB;
    matB.SetScale(3.0, 3.0,3.0);

    Eyer::EatrixF4x4 matC;
    // matC.SetRotate(0.0, 1.0, 0.0, 3.14);

    Eyer::EatrixF4x4 mp;

    EyerLog("=============================\n");
    for(int i=0;i<1;i++){
        mp = mp.Eye() * matA * matB * matC;
        mp.PrintInfo();

        ASSERT_EQ(mp.Get(0, 0), 3.0); ASSERT_EQ(mp.Get(0, 1), 0.0); ASSERT_EQ(mp.Get(0, 2), 0.0); ASSERT_EQ(mp.Get(0, 3), 3.0);
        ASSERT_EQ(mp.Get(1, 0), 0.0); ASSERT_EQ(mp.Get(1, 1), 3.0); ASSERT_EQ(mp.Get(1, 2), 0.0); ASSERT_EQ(mp.Get(1, 3), 2.0);
        ASSERT_EQ(mp.Get(2, 0), 0.0); ASSERT_EQ(mp.Get(2, 1), 0.0); ASSERT_EQ(mp.Get(2, 2), 3.0); ASSERT_EQ(mp.Get(2, 3), 5.0);
        ASSERT_EQ(mp.Get(3, 0), 0.0); ASSERT_EQ(mp.Get(3, 1), 0.0); ASSERT_EQ(mp.Get(3, 2), 0.0); ASSERT_EQ(mp.Get(3, 3), 1.0);
    }
    EyerLog("=============================\n");
}

TEST(EyerMath, Matrix4x4_Copy_Mula)
{
    Eyer::EatrixF4x4 ortho;
    ortho.SetOrtho(0.0, 729, 0.0, 1280, 100.0, -100.0);

    ortho.PrintInfo();

    Eyer::EatrixF4x4 mp;
    mp = mp.Eye() * ortho;

    mp.PrintInfo();
}

#endif //EYERLIB_MATRIXCOPY_HPP
