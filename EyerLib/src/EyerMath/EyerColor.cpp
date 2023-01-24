#include "EyerColor.hpp"

namespace Eyer
{
    EyerColor EyerColor::NO_COLOR  (0.0, 0.0, 0.0, 0.0);

    EyerColor EyerColor::RED       (1.0, 0.0, 0.0, 1.0);
    EyerColor EyerColor::GREEN     (0.0, 1.0, 0.0, 1.0);
    EyerColor EyerColor::BLUE      (0.0, 0.0, 1.0, 1.0);
    EyerColor EyerColor::YELLOW    (1.0, 1.0, 0.0, 1.0);

    EyerColor EyerColor::BLACK     (0.0, 0.0, 0.0, 1.0);
    EyerColor EyerColor::WHITE     (1.0, 1.0, 1.0, 1.0);
    EyerColor EyerColor::GRAY      (0.5, 0.5, 0.5, 1.0);

    EyerColor EyerColor::GRAY_0     (0.0, 0.0, 0.0);
    EyerColor EyerColor::GRAY_17    (17.0 / 255);
    EyerColor EyerColor::GRAY_34    (34.0 / 255);
    EyerColor EyerColor::GRAY_40    (40.0 / 255);
    EyerColor EyerColor::GRAY_51    (51.0 / 255);
    EyerColor EyerColor::GRAY_68    (68.0 / 255);
    EyerColor EyerColor::GRAY_85    (85.0 / 255);
    EyerColor EyerColor::GRAY_102   (102.0 / 255);;
    EyerColor EyerColor::GRAY_119   (119.0 / 255);
    EyerColor EyerColor::GRAY_136   (136.0 / 255);
    EyerColor EyerColor::GRAY_153   (153.0 / 255);;
    EyerColor EyerColor::GRAY_170   (170.0 / 255);;
    EyerColor EyerColor::GRAY_187   (187.0 / 255);;
    EyerColor EyerColor::GRAY_204   (204.0 / 255);;
    EyerColor EyerColor::GRAY_221   (221.0 / 255);;
    EyerColor EyerColor::GRAY_238   (238.0 / 255);;
    EyerColor EyerColor::GRAY_255   (255.0 / 255);;

    EyerColor::EyerColor()
        : EyerColor(1.0, 1.0, 1.0, 1.0)
    {

    }

    EyerColor::EyerColor(float gray)
        : EyerColor(gray, gray, gray, 1.0)
    {

    }

    EyerColor::EyerColor(float r, float g, float b, float a)
    {
        SetX(r);
        SetY(g);
        SetZ(b);
        SetW(a);
    }

    float EyerColor::r()
    {
        return x();
    }

    float EyerColor::g()
    {
        return y();
    }

    float EyerColor::b()
    {
        return z();
    }

    float EyerColor::a()
    {
        return w();
    }

    void EyerColor::r(float r)
    {
        SetX(r);
    }

    void EyerColor::g(float g)
    {
        SetY(g);
    }

    void EyerColor::b(float b)
    {
        SetZ(b);
    }

    void EyerColor::a(float a)
    {
        SetW(a);
    }
}