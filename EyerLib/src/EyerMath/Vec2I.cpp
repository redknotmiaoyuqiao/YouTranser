#include "Vec2I.hpp"

namespace Eyer
{
    Vec2I::Vec2I()
        : Vec2I(0, 0)
    {

    }

    Vec2I::Vec2I(int x, int y)
    {
        SetX(x);
        SetY(y);
    }

    Vec2I::Vec2I(const Vec2I & _vec)
    {
        *this = _vec;
    }

    int Vec2I::Zero()
    {
        SetX(0);
        SetY(0);
        return 0;
    }

    Vec2I & Vec2I::operator = (const Vec2I & _vec)
    {
        SetX(_vec.x());
        SetY(_vec.y());
        return *this;
    }

    const Vec2I Vec2I::operator + (const Vec2I & _vec) const
    {
        Vec2I res(x() + _vec.x(), y() + _vec.y());
        return res;
    }

    const Vec2I Vec2I::operator - (const Vec2I & _vec) const
    {
        Vec2I res(x() - _vec.x(), y() - _vec.y());
        return res;
    }
}