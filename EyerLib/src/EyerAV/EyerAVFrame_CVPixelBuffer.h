#ifndef EYERLIB_EYERAVFRAME_CVPIXELBUFFER_HPP
#define EYERLIB_EYERAVFRAME_CVPIXELBUFFER_HPP

extern "C"
{
    void * copyCVPixelBuffer(void * cvPixelBuffer);
    int freeCVPixelBuffer(void * cvPixelBuffer);
};

#endif //EYERLIB_EYERAVFRAME_CVPIXELBUFFER_HPP
