#ifndef EYERLIB_EYERBUFFERMUT_HPP
#define EYERLIB_EYERBUFFERMUT_HPP

#include "EyerBuffer.hpp"
#include <mutex>

namespace Eyer
{
    class EyerBufferMut : public EyerBuffer {
    public:
        EyerBufferMut();
        ~EyerBufferMut();

        EyerBufferMut(const EyerBufferMut & buffer);
        EyerBufferMut & operator = (const EyerBufferMut & buffer);

        int Append(unsigned char * _buf, int _bufLen);
        int Append(const EyerBuffer & buffer);

        int CutOff(EyerBuffer & buffer, int len);
        int CutOff(uint8_t * buffer, int len);

        int GetBuffer(unsigned char * _buf = nullptr);

        int GetLen();

        int Clear();


        int WriteDisk(EyerString & path);
        int ReadFromDisk(EyerString & path);

    private:
        std::mutex mut;
    };
}

#endif //EYERLIB_EYERBUFFERMUT_HPP
