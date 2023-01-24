#ifndef EYERLIB_EYERCROP_HPP
#define EYERLIB_EYERCROP_HPP

#include "Eatrix4x4.hpp"

namespace Eyer
{
    enum EyerCropType
    {
        FIT_CENTER = 0,
        FIT_XY = 1,
        FIT_END = 2,
        FIT_START = 3,
        CENTER_CROP = 5,

        /*
        CENTER = 4,
        CENTER_INSIDE = 6,
         */
    };

    class Eyer2DCrop {
    public:
        Eyer2DCrop(float _canvasWidth, float _canvasHeight);
        ~Eyer2DCrop();

        Eatrix4x4<float> & Crop2(float viewWidth, float viewHeight, EyerCropType cropType);
        Eatrix4x4<float> & Crop(float viewWidth, float viewHeight, EyerCropType cropType);

    public:
        float canvasWidth = 0;
        float canvasHeight = 0;

        Eatrix4x4<float> ortho;

        Eatrix4x4<float> s;
        Eatrix4x4<float> t;

        Eatrix4x4<float> scale;
        Eatrix4x4<float> trans;

        Eatrix4x4<float> res;
    };
}

#endif //EYERLIB_EYERCROP_HPP
