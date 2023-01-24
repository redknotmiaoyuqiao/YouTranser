//
// Created by yao on 2021/6/7.
//

#ifndef EYERLIB_RECTUTILTEST_HPP
#define EYERLIB_RECTUTILTEST_HPP

#include <gtest/gtest.h>
#include "EyerMath/RectUtil.hpp"
TEST(EyerMath, OverlapRectIn)
{
    Eyer::RectUtil rectUtil;
    {
        Eyer::Eect rectA(0, 0, 5, 5);
        Eyer::Eect rectB(2, 2, 5, 5);
        Eyer::Eect ret = rectUtil.OverlapRect(rectA, rectB);
        ASSERT_EQ(ret.x(), 2);
        ASSERT_EQ(ret.y(), 2);
        ASSERT_EQ(ret.w(), 3);
        ASSERT_EQ(ret.h(), 3);
    }
    {
        Eyer::Eect rectA2(0, 1, 1, 1);
        Eyer::Eect rectB2(0, 2, 2, 2);
        Eyer::Eect ret2 = rectUtil.OverlapRect(rectA2, rectB2);
        ASSERT_EQ(ret2.x(), 0);
        ASSERT_EQ(ret2.y(), 0);
        ASSERT_EQ(ret2.w(), 0);
        ASSERT_EQ(ret2.h(), 0);
    }

    {
        Eyer::Eect rectA(2, 2, 10, 10);
        Eyer::Eect rectB(4, 0, 3, 40);
        Eyer::Eect ret = rectUtil.OverlapRect(rectA, rectB);

        ASSERT_EQ(ret.x(), 4);
        ASSERT_EQ(ret.y(), 2);
        ASSERT_EQ(ret.w(), 3);
        ASSERT_EQ(ret.h(), 10);
    }
}

TEST(EyerMath, OverlapRectOut)
{
    Eyer::RectUtil rectUtil;
    Eyer::Eect rectA(-2, -2, 1, 1);
    Eyer::Eect rectB(2, 2, 5, 5);
    Eyer::Eect ret = rectUtil.OverlapRect(rectA, rectB);
    ASSERT_EQ(ret.x(), 0);
    ASSERT_EQ(ret.y(), 0);
    ASSERT_EQ(ret.w(), 0);
    ASSERT_EQ(ret.h(), 0);
}

TEST(EyerMath, OverlapRectAll)
{
    Eyer::RectUtil rectUtil;
    Eyer::Eect rectA(-2, -2, 1, 1);
    Eyer::Eect rectB(-2, -2, 1, 1);
    Eyer::Eect ret = rectUtil.OverlapRect(rectA, rectB);
    ASSERT_EQ(ret.x(), -2);
    ASSERT_EQ(ret.y(), -2);
    ASSERT_EQ(ret.w(), 1);
    ASSERT_EQ(ret.h(), 1);
}



TEST(EyerMath, OverlapRect___Bug_1)
{
    Eyer::RectUtil rectUtil;
    Eyer::Eect rectA(0.0, 0.0, 980, 280);
    Eyer::Eect rectB(189, 100, 300, 80);
    Eyer::Eect ret = rectUtil.OverlapRect(rectA, rectB);

    ASSERT_EQ(ret.x(), 189);
    ASSERT_EQ(ret.y(), 100);
    ASSERT_EQ(ret.w(), 300);
    ASSERT_EQ(ret.h(), 80);
}

TEST(EyerMath, OverlapRect___Bug_2)
{
    Eyer::RectUtil rectUtil;
    Eyer::Eect rectA(0.0, 0.0, 980, 280);
    Eyer::Eect rectB(261, 104, 300, 80);
    Eyer::Eect ret = rectUtil.OverlapRect(rectA, rectB);

    ASSERT_EQ(ret.x(), 261);
    ASSERT_EQ(ret.y(), 104);
    ASSERT_EQ(ret.w(), 300);
    ASSERT_EQ(ret.h(), 80);
}

TEST(EyerMath, PointInRect)
{
    Eyer::RectUtil rectUtil;

    Eyer::EectorF4 rect(0.0, 0.0, 980, 280);
    Eyer::EectorF2 point(1.0, 1.0);
    bool ret = rectUtil.PointInRect(rect, point);

    ASSERT_EQ(ret, true);

    Eyer::EectorF4 rect2(0.0, 0.0, 980, 280);
    Eyer::EectorF2 point2(1000.0, 1000.0);
    ret = rectUtil.PointInRect(rect2, point2);
    ASSERT_EQ(ret, false);

    Eyer::EectorF4 rect3(-10.0, -10.0, 10, 10);
    Eyer::EectorF2 point3(-10.0, -10.0);
    ret = rectUtil.PointInRect(rect3, point3);
    ASSERT_EQ(ret, true);

}

TEST(EyerMath, PointInRect2)
{
    Eyer::RectUtil rectUtil;

    Eyer::EectorF4 rect(2.0, -2.0, 3, 2);
    Eyer::EectorF2 point(3.0, -1.0);
    Eyer::EectorF2 point2(6.0, -2.0);
    Eyer::EectorF2 point3(5.0, -3.0);

    bool ret = rectUtil.PointInRect(rect, point);
    ASSERT_EQ(ret, true);
    ret = rectUtil.PointInRect(rect, point2);
    ASSERT_EQ(ret, false);
    ret = rectUtil.PointInRect(rect, point3);
    ASSERT_EQ(ret, false);
}

TEST(EyerMath, PointXCrossRect)
{
    Eyer::RectUtil rectUtil;

    Eyer::EectorF4 rect(2.0, -2.0, 3, 2);
    Eyer::EectorF2 point(3.0, -1.0);
    Eyer::EectorF2 point2(6.0, -2.0);
    Eyer::EectorF2 point3(5.0, -3.0);

    bool ret = rectUtil.PointXCrossRect(rect, point);
    ASSERT_EQ(ret, true);
    ret = rectUtil.PointXCrossRect(rect, point2);
    ASSERT_EQ(ret, true);
    ret = rectUtil.PointXCrossRect(rect, point3);
    ASSERT_EQ(ret, false);
}

TEST(EyerMath, PointXCrossRect2)
{
    Eyer::RectUtil rectUtil;

    Eyer::EectorF4 rect(-1.0, -1.0, 2, 2);
    Eyer::EectorF2 point(1.0, -1.0);
    Eyer::EectorF2 point2(2.0, 0.0);
    Eyer::EectorF2 point3(2.0, 3.0);

    bool ret = rectUtil.PointXCrossRect(rect, point);
    EyerLog("%d\n", ret);
    ASSERT_EQ(ret, true);
    ret = rectUtil.PointXCrossRect(rect, point2);
    EyerLog("%d\n", ret);
    ASSERT_EQ(ret, true);
    ret = rectUtil.PointXCrossRect(rect, point3);
    EyerLog("%d\n", ret);
    ASSERT_EQ(ret, false);
}
#endif //EYERLIB_RECTUTILTEST_HPP
