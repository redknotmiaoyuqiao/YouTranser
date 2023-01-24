#include "Eect.hpp"

namespace Eyer
{
    Eect::Eect()
    {

    }

    Eect::Eect(float x, float y, float w, float h)
    {
        SetXY(x, y);
        SetWH(w, h);
    }

    Eect::Eect(const Eatrix2x1<float> & pos, const Eatrix2x1<float> & wh)
    {
        SetXY(pos);
        SetWH(wh);
    }

    Eect::Eect(const Eect & rect)
    {
        *this = rect;
    }

    Eect::~Eect()
    {

    }

    const Eect & Eect::operator = (const Eect & rect)
    {
        pos = rect.pos;
        wh = rect.wh;
        return *this;
    }

    float Eect::GetX()
    {
        return pos.x();
    }

    float Eect::GetY()
    {
        return pos.y();
    }

    float Eect::GetW()
    {
        return wh.x();
    }

    float Eect::GetH()
    {
        return wh.y();
    }





    float Eect::x() const
    {
        return pos.x();
    }

    float Eect::y() const
    {
        return pos.y();
    }

    float Eect::w() const
    {
        return wh.w();
    }

    float Eect::h() const
    {
        return wh.h();
    }




    int Eect::SetXY(float x, float y)
    {
        pos.SetX(x);
        pos.SetY(y);
        return 0;
    }

    int Eect::SetWH(float w, float h)
    {
        wh.SetX(w);
        wh.SetY(h);
        return 0;
    }

    int Eect::SetXY(const Eatrix2x1<float> & _pos)
    {
        pos = _pos;
        return 0;
    }

    int Eect::SetWH(const Eatrix2x1<float> & _wh)
    {
        wh = _wh;
        return 0;
    }

    bool Eect::IsIn(const Eatrix2x1<float> & touchPos)
    {
        // Start =
        Eatrix2x1<float> startPos = pos;
        Eatrix2x1<float> endPos(pos.x() + wh.w(), pos.y() + wh.h());

        if(touchPos.x() < startPos.x() || touchPos.y() < startPos.y()){
            return false;
        }

        if(touchPos.x() > endPos.x() || touchPos.y() > endPos.y()){
            return false;
        }

        return true;
    }

    bool Eect::IsInLine(const Eatrix2x1<float> & start, const Eatrix2x1<float> & end)
    {
        //判断线段的两端点是否至少有一个在矩形内部
        if(IsIn(start) || IsIn(end)){
            return true;
        }

        //判断线段是否与矩形对角线相交
        Eatrix2x1<float> rightBottom(pos.x() + wh.w(), pos.y() + wh.h());
        Eatrix2x1<float> leftBottom(pos.x(), pos.y() + wh.h());
        Eatrix2x1<float> rightTop(pos.x() + wh.w(), pos.y());

        if(Eath::IsLineCross(start, end, pos, rightBottom)){
            return true;
        }

        if(Eath::IsLineCross(start, end, leftBottom, rightTop)){
            return true;
        }

        return false;
    }
}