#include "EyerBufferMut.hpp"

namespace Eyer
{
    EyerBufferMut::EyerBufferMut() : EyerBuffer()
    {

    }

    EyerBufferMut::~EyerBufferMut()
    {
        Clear();
    }

    EyerBufferMut::EyerBufferMut(const EyerBufferMut & buffer) : EyerBufferMut()
    {
        *this = buffer;
    }

    EyerBufferMut & EyerBufferMut::operator = (const EyerBufferMut & buffer)
    {
        std::lock_guard<std::mutex> lg(mut);
        EyerBuffer::operator=(buffer);
        return *this;
    }

    int EyerBufferMut::Append(unsigned char * _buf, int _bufLen)
    {
        std::lock_guard<std::mutex> lg(mut);
        return EyerBuffer::Append(_buf, _bufLen);
    }

    int EyerBufferMut::Append(const EyerBuffer & buffer)
    {
        std::lock_guard<std::mutex> lg(mut);
        return EyerBuffer::Append(buffer);
    }

    int EyerBufferMut::CutOff(EyerBuffer & buffer, int len)
    {
        std::lock_guard<std::mutex> lg(mut);
        return EyerBuffer::CutOff(buffer, len);
    }

    int EyerBufferMut::CutOff(uint8_t * buffer, int len)
    {
        std::lock_guard<std::mutex> lg(mut);
        return EyerBuffer::CutOff(buffer, len);
    }

    int EyerBufferMut::GetBuffer(unsigned char * _buf)
    {
        std::lock_guard<std::mutex> lg(mut);
        return EyerBuffer::GetBuffer(_buf);
    }

    int EyerBufferMut::GetLen()
    {
        std::lock_guard<std::mutex> lg(mut);
        return EyerBuffer::GetLen();
    }

    int EyerBufferMut::Clear()
    {
        std::lock_guard<std::mutex> lg(mut);
        return EyerBuffer::Clear();
    }

    int EyerBufferMut::WriteDisk(EyerString & path)
    {
        std::lock_guard<std::mutex> lg(mut);
        return EyerBuffer::WriteDisk(path);
    }

    int EyerBufferMut::ReadFromDisk(EyerString & path)
    {
        std::lock_guard<std::mutex> lg(mut);
        return EyerBuffer::ReadFromDisk(path);
    }
}