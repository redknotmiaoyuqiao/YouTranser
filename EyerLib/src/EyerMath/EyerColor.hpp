#ifndef EYERLIB_EYERCOLOR_HPP
#define EYERLIB_EYERCOLOR_HPP

#include "Eatrix3x1.hpp"
#include "Eatrix4x1.hpp"

namespace Eyer
{
    class EyerColor : public Eatrix4x1<float>
    {
    public:
        static EyerColor NO_COLOR;
        static EyerColor RED;
        static EyerColor GREEN;
        static EyerColor BLUE;
        static EyerColor YELLOW;

        static EyerColor BLACK;
        static EyerColor WHITE;
        static EyerColor GRAY;

        static EyerColor GRAY_0;
        static EyerColor GRAY_17;
        static EyerColor GRAY_34;
        static EyerColor GRAY_40;
        static EyerColor GRAY_51;
        static EyerColor GRAY_68;
        static EyerColor GRAY_85;
        static EyerColor GRAY_102;
        static EyerColor GRAY_119;
        static EyerColor GRAY_136;
        static EyerColor GRAY_153;
        static EyerColor GRAY_170;
        static EyerColor GRAY_187;
        static EyerColor GRAY_204;
        static EyerColor GRAY_221;
        static EyerColor GRAY_238;
        static EyerColor GRAY_255;

    public:
        EyerColor();
        EyerColor(float gray);
        EyerColor(float r, float g, float b, float a = 1.0);

        float r();
        float g();
        float b();
        float a();

        void r(float r);
        void g(float g);
        void b(float b);
        void a(float a);
    };
}

#endif //EYERLIB_EYERCOLOR_HPP
