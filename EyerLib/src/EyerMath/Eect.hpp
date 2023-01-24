#ifndef EYERLIB_EECT_HPP
#define EYERLIB_EECT_HPP

#include "Eatrix4x1.hpp"
#include "Eatrix2x1.hpp"
#include "Eath.hpp"

namespace Eyer
{
    class Eect
    {
    public:
        Eect();
        Eect(float x, float y, float w, float h);
        Eect(const Eatrix2x1<float> & pos, const Eatrix2x1<float> & wh);
        Eect(const Eect & rect);
        ~Eect();

        const Eect & operator = (const Eect & rect);

        float GetX();
        float GetY();

        float GetW();
        float GetH();

        float x() const;
        float y() const;

        float w() const;
        float h() const;

        int SetXY(float x = 0.0f, float y = 0.0f);
        int SetWH(float w, float h);

        int SetXY(const Eatrix2x1<float> & pos);
        int SetWH(const Eatrix2x1<float> & wh);

        bool IsInLine(const Eatrix2x1<float> & start, const Eatrix2x1<float> & end);

        bool IsIn(const Eatrix2x1<float> & pos);
    public:
        Eatrix2x1<float> pos;
        Eatrix2x1<float> wh;
    };
}

#endif //EYERLIB_EECT_HPP
