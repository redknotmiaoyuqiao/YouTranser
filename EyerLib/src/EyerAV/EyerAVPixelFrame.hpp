#ifndef EYERCAMERAANDROID_EYERAVPIXELFRAME_HPP
#define EYERCAMERAANDROID_EYERAVPIXELFRAME_HPP

#include "EyerAVPixelFormat.hpp"
#include <stdint.h>

namespace Eyer
{
    class EyerAVPixelFrame
    {
    public:
        EyerAVPixelFrame();
        EyerAVPixelFrame(int _w, int _h);
        ~EyerAVPixelFrame();

        int Alloc(int _w, int _h);

        uint8_t * GetData() const;

        int GetWidth() const;
        int GetHeight() const;

    private:
        int w = 0;
        int h = 0;
        EyerAVPixelFormat pixelFormat;

        uint8_t * buffer = nullptr;
    };
};

#endif //EYERCAMERAANDROID_EYERAVPIXELFRAME_HPP
