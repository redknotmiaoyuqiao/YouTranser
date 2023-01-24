#include "EyerRectI.hpp"

namespace Eyer
{
    EyerRectI::EyerRectI(int x, int y, int w, int h)
        : xy(x, y)
        , wh(w, h)
    {

    }

    EyerRectI::EyerRectI()
    {
        xy.SetX(0);
        xy.SetY(0);
        wh.SetX(0);
        wh.SetY(0);
    }

    EyerRectI::~EyerRectI()
    {

    }

    EyerRectI::EyerRectI(const EyerRectI & _rect)
    {
        *this = _rect;
    }

    EyerRectI & EyerRectI::operator = (const EyerRectI & _rect)
    {
        xy = _rect.xy;
        wh = _rect.wh;
        return *this;
    }
}