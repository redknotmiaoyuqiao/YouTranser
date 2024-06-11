#include "EyerBuffer.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "EyerLog.hpp"

namespace Eyer
{
    EyerBuffer::EyerBuffer()
    {
        buf = nullptr;
        bufLen = 0;
    }

    EyerBuffer::EyerBuffer(uint8_t * _buf, int _bufLen)
        : EyerBuffer()
    {
        if(buf != nullptr){
            free(buf);
            buf = nullptr;
        }
        bufLen = _bufLen;
        buf = (uint8_t *)malloc(bufLen);
        memcpy(buf, _buf, bufLen);
    }

    EyerBuffer::EyerBuffer(int size)
        : EyerBuffer()
    {
        if(buf != nullptr){
            free(buf);
            buf = nullptr;
        }
        bufLen = size;
        buf = (uint8_t *)malloc(bufLen);
        memset(buf, 0, bufLen);
    }

    EyerBuffer::~EyerBuffer()
    {
        Clear();
    }

    EyerBuffer::EyerBuffer(const EyerBuffer & buffer) : EyerBuffer()
    {
        *this = buffer;
    }

    EyerBuffer & EyerBuffer::operator = (const EyerBuffer & buffer)
    {
        if(buf != nullptr){
            free(buf);
            buf = nullptr;
        }
        bufLen = buffer.GetLen();
        buf = (uint8_t *)malloc(bufLen);
        memcpy(buf, buffer.GetPtr(), bufLen);
        return *this;
    }

    int EyerBuffer::Append(uint8_t * _buf, int _bufLen)
    {
        int newLen = bufLen + _bufLen;
        uint8_t * newBuf = (uint8_t *)malloc(newLen);

        memcpy(newBuf, buf, bufLen);
        memcpy(newBuf + bufLen, _buf, _bufLen);

        if(buf != nullptr){
            free(buf);
            buf = nullptr;
        }

        buf = newBuf;
        bufLen = newLen;

        return 0;
    }

    int EyerBuffer::Append(const EyerBuffer & buffer)
    {
        return Append(buffer.buf, buffer.bufLen);
    }

    int EyerBuffer::CutOff(uint8_t * buffer, int len)
    {
        if(len <= 0){
            return 0;
        }

        if(len > bufLen){
            len = bufLen;
        }

        memcpy(buffer, buf, len);

        int newLen = bufLen - len;
        uint8_t * newBuf = (uint8_t *)malloc(newLen);

        memcpy(newBuf, buf + len, newLen);

        if(buf != nullptr){
            free(buf);
            buf = nullptr;
        }

        buf = newBuf;
        bufLen = newLen;

        return len;
    }

    int EyerBuffer::CutOff(EyerBuffer & buffer, int len)
    {
        uint8_t * tempBuffer = (uint8_t *)malloc(len);

        int l = CutOff(tempBuffer, len);

        buffer.Clear();
        buffer.Append(tempBuffer, l);

        if(tempBuffer != nullptr){
            free(tempBuffer);
            tempBuffer = nullptr;
        }

        return l;
    }

    int EyerBuffer::GetBuffer(uint8_t * _buf) const
    {
        if(_buf == nullptr){
            return bufLen;
        }

        memcpy(_buf, buf, bufLen);

        return 0;
    }

    int EyerBuffer::Clear()
    {
        if(buf != nullptr){
            free(buf);
            buf = nullptr;
        }
        bufLen = 0;
        buf = nullptr;
        return 0;
    }

    int EyerBuffer::WriteDisk(const EyerString & path) const
    {
        FILE * f = fopen(path.c_str(), "wb");
        if(f == nullptr){
            return -1;
        }

        fwrite(buf, bufLen, 1, f);

        fclose(f);

        return 0;
    }

    int EyerBuffer::ReadFromDisk(const EyerString & path)
    {
        FILE * f = fopen(path.c_str(), "rb");
        if(f == nullptr){
            return -1;
        }

        fseek(f, 0L, SEEK_END);
        int tempBufLen = ftell(f);

        fseek(f, 0L, SEEK_SET);

        uint8_t * tempBuf = (uint8_t *)malloc(tempBufLen);
        fread(tempBuf, tempBufLen, 1, f);

        fclose(f);

        {
            Clear();
            Append(tempBuf, tempBufLen);
        }

        if(tempBuf != nullptr){
            free(tempBuf);
            tempBuf = nullptr;
        }

        return 0;
    }

    uint8_t * EyerBuffer::GetPtr() const
    {
        return buf;
    }

    int EyerBuffer::GetLen() const
    {
        return bufLen;
    }

    int EyerBuffer::SetLen(int len)
    {
        bufLen = len;
        return 0;
    }
}
