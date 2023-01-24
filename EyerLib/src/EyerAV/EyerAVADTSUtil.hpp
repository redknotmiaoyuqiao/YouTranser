#ifndef EYERLIB_EYERAVADTSUTIL_HPP
#define EYERLIB_EYERAVADTSUTIL_HPP

#include <stdint.h>
#include "EyerCore/EyerCore.hpp"
#include "EyerAVADTS.hpp"

namespace Eyer
{
    typedef struct
    {
        int write_adts;
        int objecttype;
        int sample_rate_index;
        int channel_conf;
    } ADTSContext;

    class EyerAVADTSUtil {
    public:
        EyerAVADTS GetADTS(unsigned char * extradataBuf, int extradataBufSize, int dataLen);

    private:
        int AACDecodeExtradata(ADTSContext * adts, unsigned char * pbuf, int bufsize);
        int AACSetAdtsHead(ADTSContext * acfg, unsigned char * buf, int size);
    };
}

#endif //EYERLIB_EYERAVADTSUTIL_HPP
