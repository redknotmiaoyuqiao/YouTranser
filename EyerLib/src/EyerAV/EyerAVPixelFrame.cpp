#include "EyerAVPixelFrame.hpp"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

namespace Eyer
{
    EyerAVPixelFrame::EyerAVPixelFrame()
    {

    }

    EyerAVPixelFrame::EyerAVPixelFrame(int _w, int _h)
    {
        w = _w;
        h = _h;
        pixelFormat = EyerAVPixelFormat::EYER_RGBA;
        buffer = (uint8_t *)malloc(w * h * 4);
    }

    EyerAVPixelFrame::~EyerAVPixelFrame()
    {
        if(buffer != nullptr){
            free(buffer);
            buffer = nullptr;
        }
    }

    int EyerAVPixelFrame::Alloc(int _w, int _h)
    {
        if(_w != w || _h != h){
            // Realloc
            if(buffer != nullptr){
                free(buffer);
                buffer = nullptr;
            }
            w = _w;
            h = _h;
            pixelFormat = EyerAVPixelFormat::EYER_RGBA;
            buffer = (uint8_t *)malloc(w * h * 4);
        }
        return 0;
    }

    uint8_t * EyerAVPixelFrame::GetData() const
    {
        return buffer;
    }

    int EyerAVPixelFrame::GetWidth() const
    {
        return w;
    }

    int EyerAVPixelFrame::GetHeight() const
    {
        return h;
    }
}