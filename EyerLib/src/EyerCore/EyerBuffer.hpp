#ifndef EYE_LIB_EYERBUFFER_HPP
#define EYE_LIB_EYERBUFFER_HPP

#include <stdint.h>
#include <mutex>
#include "EyerString.hpp"

namespace Eyer{
    class EyerBuffer {
    public:
        EyerBuffer();
        EyerBuffer(int size);
        EyerBuffer(uint8_t * _buf, int _bufLen);
        ~EyerBuffer();

        EyerBuffer(const EyerBuffer & buffer);
        EyerBuffer & operator = (const EyerBuffer & buffer);

        int Append(uint8_t * _buf, int _bufLen);
        int Append(const EyerBuffer & buffer);

        int CutOff(EyerBuffer & buffer, int len);
        int CutOff(uint8_t * buffer, int len);

        int GetBuffer(uint8_t * _buf = nullptr) const;

        int Clear();

        int WriteDisk(const EyerString & path) const;
        int ReadFromDisk(const EyerString & path);

        uint8_t * GetPtr() const;
        int GetLen() const;

        int SetLen(int len);

    private:
        uint8_t * buf = nullptr;
        int bufLen = 0;
    };
}

#endif //EYE_LIB_EYERBUFFER_HPP
