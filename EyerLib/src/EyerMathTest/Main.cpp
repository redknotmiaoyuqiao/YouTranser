#include <gtest/gtest.h>
#include "EyerMath/EyerMath.hpp"

#include "MatrixMove.hpp"
#include "MatrixInvert.hpp"
#include "MatrixTranspose.hpp"
#include "RectUtilTest.hpp"

#include "Vec2ITest.hpp"

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}