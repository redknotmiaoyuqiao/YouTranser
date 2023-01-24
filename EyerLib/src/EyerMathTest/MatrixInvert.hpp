#ifndef EYERLIB_MATRIXINVERT_HPP
#define EYERLIB_MATRIXINVERT_HPP

#include <gtest/gtest.h>
#include "EyerMath/Eath.hpp"

TEST(EyerMath, Matrix4x4_Invert){
    {
        Eyer::Eatrix4x4<float> a;
        a.SetOrtho(0.0, 100.0, 0.0, 100.0, 0.1, 1000.0);
        a.PrintInfo();

        Eyer::Eatrix4x4<float> res = !a;
        res.PrintInfo();

        Eyer::Eatrix4x4<float> res2 = res * a;
        res2.PrintInfo();

        res2 = a * res;
        res2.PrintInfo();
    }

    {
        Eyer::Eatrix3x3<float> rgb2020_xyz_mat;

        float rgb2020_xyz[] = {
                0.6370, 0.1446, 0.1689,
                0.2627, 0.6780, 0.0593,
                0, 0.0281, 1.0610
        };
        rgb2020_xyz_mat.SetData(rgb2020_xyz, 9);
        rgb2020_xyz_mat.PrintInfo();

        Eyer::Eatrix3x3<float> rgb2020_xyz_mat__ = !rgb2020_xyz_mat;
        rgb2020_xyz_mat__.PrintInfo();

        Eyer::Eatrix3x3<float> res = rgb2020_xyz_mat * rgb2020_xyz_mat__;
        res.PrintInfo();

        res = rgb2020_xyz_mat__ * rgb2020_xyz_mat;
        res.PrintInfo();
    }
}


#endif //EYERLIB_MATRIXINVERT_HPP
