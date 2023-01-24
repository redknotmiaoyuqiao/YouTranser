#ifndef EYE_LIB_EYERBUFFER_HPP
#define EYE_LIB_EYERBUFFER_HPP

#include <stdint.h>
#include <mutex>
#include "EyerString.hpp"

#define EYER_BUFFER_CACHE_SIZE 1024*1024

namespace Eyer{
    class EyerBuffer {
    public:
        EyerBuffer(int size = EYER_BUFFER_CACHE_SIZE);
        EyerBuffer(uint8_t * _buf, int _bufLen);
        ~EyerBuffer();

        EyerBuffer(const EyerBuffer & buffer);
        EyerBuffer & operator = (const EyerBuffer & buffer);

        int Append(uint8_t * _buf, int _bufLen);
        int Append(const EyerBuffer & buffer);

        int CutOff(EyerBuffer & buffer, int len);
        int CutOff(uint8_t * buffer, int len);

        int GetBuffer(uint8_t * _buf = nullptr) const;

        int GetLen() const;
        int SetLen(int _len);

        int Clear();

        int WriteDisk(EyerString & path);
        int ReadFromDisk(EyerString & path);

        uint8_t * GetPtr() const;

        int PrintfDebug();

    private:
        uint8_t * originBuf = nullptr;
        int originBufLen = 0;

        uint8_t * buf = nullptr;
        int bufLen = 0;

        int ReAlloc(uint8_t ** buf, int len);
        int ReAlloc(int len);

        int mallocTimes = 0;
    };
}

#endif //EYE_LIB_EYERBUFFER_HPP
