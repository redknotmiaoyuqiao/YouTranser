#ifndef EYERLIB_VEC2ITEST_HPP
#define EYERLIB_VEC2ITEST_HPP

#include <gtest/gtest.h>
#include "EyerMath/EyerMath.hpp"

TEST(EyerMath, Vec2I)
{
    Eyer::Vec2I v(1, 100);
    ASSERT_EQ(1, v.x());
    ASSERT_EQ(100, v.y());

    Eyer::Vec2I v2 = v;
    ASSERT_EQ(v.x(), v2.x());
    ASSERT_EQ(v.y(), v2.y());

    Eyer::Vec2I v3;
    v3 = v;
    ASSERT_EQ(v.x(), v3.x());
    ASSERT_EQ(v.y(), v3.y());
}

TEST(EyerMath, Vec2I_ADD)
{
    Eyer::Vec2I a(100, 50);
    Eyer::Vec2I b(100, 50);

    Eyer::Vec2I c = a + b;

    ASSERT_EQ(c.x(), 200);
    ASSERT_EQ(c.y(), 100);
}

#endif //EYERLIB_VEC2ITEST_HPP
