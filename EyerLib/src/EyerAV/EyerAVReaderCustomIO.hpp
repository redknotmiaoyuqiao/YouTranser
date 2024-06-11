#ifndef EYERAVREADERCUSTOMIO_HPP
#define EYERAVREADERCUSTOMIO_HPP

#include <stdint.h>

namespace Eyer
{
    class EyerAVReaderCustomIO
    {
    public:
        virtual ~EyerAVReaderCustomIO(){}
        virtual int Read(uint8_t *buf, int buf_size) = 0;
        virtual int64_t Seek(int64_t offset, int whence) = 0;
    };
}

#endif //EYERAVREADERCUSTOMIO_HPP
