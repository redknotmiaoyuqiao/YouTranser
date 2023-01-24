#ifndef EYERLIB_VEC2I_HPP
#define EYERLIB_VEC2I_HPP

#include "Eatrix2x1.hpp"

namespace Eyer
{
    class Vec2I : public Eatrix2x1<int>
    {
    public:
        Vec2I();
        Vec2I(int x, int y);

        Vec2I(const Vec2I & _vec);
        Vec2I & operator = (const Vec2I & _vec);

        int Zero();

        const Vec2I operator + (const Vec2I & _vec) const;
        const Vec2I operator - (const Vec2I & _vec) const;
    };
}

#endif //EYERLIB_VEC2I_HPP
