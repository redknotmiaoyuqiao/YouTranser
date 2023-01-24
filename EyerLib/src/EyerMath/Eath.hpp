#ifndef EYERLIB_EATH_HPP
#define EYERLIB_EATH_HPP

#define EYER_PI 3.14159265358979323846

#include "Eatrix2x1.hpp"

namespace Eyer
{
    class Eath {
    public:
        static float DegreesToRadians(float degrees);

        //差积
        static float DifferenceProduct(const Eatrix2x1<float> & a, const Eatrix2x1<float> & b, const Eatrix2x1<float> & c);

        /**
         * 判断两线段是否相交
         * @param a,b表示一条线段  c,d表示一条线段
         * @return 相交返回true，不相交返回false
         */
        static bool IsLineCross(const Eatrix2x1<float> & a, const Eatrix2x1<float> & b, const Eatrix2x1<float> & c, const Eatrix2x1<float> & d);

        static int GetGreatestCommonDivisor(int a, int b);
    };
}
#endif //EYERLIB_EATH_HPP
