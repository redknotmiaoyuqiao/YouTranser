#include "EyerAVFrame_CVPixelBuffer.h"

#import <AVFoundation/AVFoundation.h>
#import <VideoToolbox/VideoToolbox.h>


void * copyCVPixelBuffer(void * cvPixelBuffer)
{
    CVImageBufferRef imageBuffer = CVBufferRetain((CVImageBufferRef)cvPixelBuffer);
    return imageBuffer;
}

int freeCVPixelBuffer(void * cvPixelBuffer)
{
    CVBufferRelease((CVImageBufferRef)cvPixelBuffer);
    return 0;
}