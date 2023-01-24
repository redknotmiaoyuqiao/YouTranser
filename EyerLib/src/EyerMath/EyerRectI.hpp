#ifndef EYERLIB_EYERRECTI_HPP
#define EYERLIB_EYERRECTI_HPP

#include "Vec2I.hpp"

namespace Eyer
{
    class EyerRectI
    {
    public:
        EyerRectI(int x, int y, int w, int h);
        EyerRectI();
        ~EyerRectI();

        EyerRectI(const EyerRectI & _rect);
        EyerRectI & operator = (const EyerRectI & _rect);

    public:
        Vec2I xy;
        Vec2I wh;
    };
}

#endif //EYERLIB_EYERRECTI_HPP
