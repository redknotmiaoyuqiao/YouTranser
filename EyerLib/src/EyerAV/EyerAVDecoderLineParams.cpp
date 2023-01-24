#include "EyerAVDecoderLineParams.hpp"

namespace Eyer
{
    EyerAVDecoderLineParams::EyerAVDecoderLineParams()
    {
        lineCacheMaxFrame = 5;
        isScale = false;
        pixelFormat = EyerAVPixelFormat::EYER_RGBA;
        scaleWidth = 0;
        scaleHeight = 0;
    }

    EyerAVDecoderLineParams::EyerAVDecoderLineParams(int _lineCacheMaxFrame)
    {
        lineCacheMaxFrame = _lineCacheMaxFrame;
        isScale = false;
        pixelFormat = EyerAVPixelFormat::EYER_RGBA;
        scaleWidth = 0;
        scaleHeight = 0;
    }

    EyerAVDecoderLineParams::~EyerAVDecoderLineParams()
    {

    }

    int EyerAVDecoderLineParams::SetScale(const EyerAVPixelFormat & _pixelFormat, int _scaleWidth, int _scaleHeight)
    {
        isScale         = true;
        pixelFormat     = _pixelFormat;
        scaleWidth      = _scaleWidth;
        scaleHeight     = _scaleHeight;
        return 0;
    }
}