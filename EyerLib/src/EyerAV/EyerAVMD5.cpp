#include "EyerAVMD5.hpp"

#include <stdint.h>
#include <string>
#include <string.h>

#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    void EyerAVMD5::gogogo()
    {
        // int LEN = 1024 * 1024;
        int LEN = 1;
        uint8_t * buf = (uint8_t *)malloc(LEN);

        for(int i=0;i<LEN;i++){
            buf[i] = i;
        }


        AVMD5 *context = av_md5_alloc();
        av_md5_init(context);

        av_md5_update(context, buf, LEN);

        uint8_t checksum[16];
        av_md5_final(context, checksum);

        av_freep(&context);

        for(int i=0;i<16;i++){
            printf("%02x ", checksum[i]);
        }
        printf("\n");

        free(buf);
    }
}