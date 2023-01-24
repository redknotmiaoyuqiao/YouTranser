//
// Created by chuchun on 2021/6/30.
//

#ifndef EYERLIB_EECTTEST_H
#define EYERLIB_EECTTEST_H

#include <gtest/gtest.h>
#include "EyerMath/Eect.hpp"

TEST(EyerMath, IsCrossRect)
{
    Eyer::Eect rect(-2, -2, 3, 3);

    Eyer::Eatrix2x1<float> start(2, 0);
    Eyer::Eatrix2x1<float> end(0, 2);
    int ret = rect.IsInLine(start, end);
    ASSERT_EQ(ret, true);

    ret = rect.IsInLine(end, start);
    ASSERT_EQ(ret, true);

    Eyer::Eatrix2x1<float> start2(0, -4);
    Eyer::Eatrix2x1<float> end2(4, 0);
    ret = rect.IsInLine(start2, end2);
    ASSERT_EQ(ret, false);

    rect.IsInLine(end2, start2);
    ASSERT_EQ(ret, false);

    Eyer::Eatrix2x1<float> start3(0, -1);
    Eyer::Eatrix2x1<float> end3(-1, 0);
    ret = rect.IsInLine(start3, end3);
    ASSERT_EQ(ret, true);

    rect.IsInLine(end3, start3);
    ASSERT_EQ(ret, true);

    Eyer::Eatrix2x1<float> start4(0, 0);
    Eyer::Eatrix2x1<float> end4(0, 2);
    ret = rect.IsInLine(start4, end4);
    ASSERT_EQ(ret, true);

    rect.IsInLine(end4, start4);
    ASSERT_EQ(ret, true);

    Eyer::Eatrix2x1<float> start5(-3, 0);
    Eyer::Eatrix2x1<float> end5(-3, 2);
    ret = rect.IsInLine(start5, end5);
    ASSERT_EQ(ret, false);

    rect.IsInLine(end5, start5);
    ASSERT_EQ(ret, false);

    Eyer::Eatrix2x1<float> start6(-3, 1);
    Eyer::Eatrix2x1<float> end6(-4, 2);
    ret = rect.IsInLine(start6, end6);
    ASSERT_EQ(ret, false);

    rect.IsInLine(end6, start6);
    ASSERT_EQ(ret, false);

    Eyer::Eatrix2x1<float> start7(2, 1);
    Eyer::Eatrix2x1<float> end7(3, 1);
    ret = rect.IsInLine(start7, end7);
    ASSERT_EQ(ret, false);

    rect.IsInLine(end7, start7);
    ASSERT_EQ(ret, false);
}

#endif //EYERLIB_EECTTEST_H
