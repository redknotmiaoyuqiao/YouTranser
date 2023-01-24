#include "EyerBuffer.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "EyerLog.hpp"

namespace Eyer{
    int EyerBuffer::ReAlloc(uint8_t ** targetBuf, int targetLen)
    {
        // 计算剩余空间
        int size = originBufLen - (buf - originBuf);
        if(targetLen > size) {
            // 重新分配空间
            int targetBufLen = targetLen * 3;
            *targetBuf = (uint8_t *)malloc(targetBufLen);

            mallocTimes++;

            return targetBufLen;
        }

        return 0;
    }

    int EyerBuffer::ReAlloc(int len)
    {
        uint8_t * targetBuf = nullptr;
        int ret = ReAlloc(&targetBuf, len);
        if(ret > 0){
            if(originBuf != nullptr){
                free(originBuf);
                originBuf = nullptr;
            }
            originBuf = targetBuf;
            originBufLen = ret;
        }

        buf = originBuf;
        bufLen = len;

        return len;
    }

    EyerBuffer::EyerBuffer(int size)
    {
        uint8_t * targetBuf = nullptr;
        int ret = ReAlloc(&targetBuf, size);
        if(ret > 0){
            originBuf = targetBuf;
            originBufLen = ret;
        }

        buf = originBuf;
        bufLen = 0;
    }

    EyerBuffer::EyerBuffer(uint8_t * _buf, int _bufLen) : EyerBuffer(_bufLen)
    {
        memcpy(buf, _buf, _bufLen);
        bufLen = _bufLen;
    }

    EyerBuffer::~EyerBuffer()
    {
        Clear();

        if(originBuf != nullptr){
            free(originBuf);
            originBuf = nullptr;
        }
        originBufLen = 0;
    }

    EyerBuffer::EyerBuffer(const EyerBuffer & buffer) : EyerBuffer()
    {
        *this = buffer;
    }

    EyerBuffer & EyerBuffer::operator = (const EyerBuffer & buffer)
    {
        uint8_t * targetBuf = nullptr;
        int ret = ReAlloc(&targetBuf, buffer.bufLen);
        if(ret > 0){
            originBuf = targetBuf;
            originBufLen = ret;
        }

        buf = originBuf;

        bufLen = buffer.bufLen;
        memcpy(buf, buffer.buf, bufLen);

        return *this;
    }

    int EyerBuffer::Append(uint8_t * _buf, int _bufLen)
    {
        uint8_t * targetBuf = nullptr;
        int targetSize = bufLen + _bufLen;
        int ret = ReAlloc(&targetBuf, targetSize);
        if(ret > 0){
            // 分配了新的内存
            // 先拷贝旧的数据
            memcpy(targetBuf, buf, bufLen);
            // 再拷贝新进来的数据
            memcpy(targetBuf + bufLen, _buf, _bufLen);

            if(originBuf != nullptr){
                free(originBuf);
                originBuf = nullptr;
            }

            originBuf = targetBuf;
            originBufLen = ret;

            buf = originBuf;
            bufLen = targetSize;
        }
        else {
            // 没有分配新的内存
            memcpy(buf + bufLen, _buf, _bufLen);
            bufLen = targetSize;
        }

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
        buf = buf + len;
        bufLen = bufLen - len;

        return len;
    }

    int EyerBuffer::CutOff(EyerBuffer & buffer, int len)
    {
        buffer.ReAlloc(len);

        int ret = CutOff(buffer.GetPtr(), len);
        return ret;
    }

    int EyerBuffer::GetBuffer(uint8_t * _buf) const
    {
        if(_buf == nullptr){
            return bufLen;
        }

        memcpy(_buf, buf, bufLen);

        return 0;
    }

    int EyerBuffer::GetLen() const
    {
        return GetBuffer();
    }

    int EyerBuffer::SetLen(int _len)
    {
        bufLen = _len;
        return 0;
    }

    int EyerBuffer::Clear()
    {
        buf = originBuf;
        bufLen = 0;
        return 0;
    }

    int EyerBuffer::WriteDisk(EyerString & path)
    {
        FILE * f = fopen(path.c_str(), "wb");
        if(f == nullptr){
            return -1;
        }

        fwrite(buf, bufLen, 1, f);

        fclose(f);

        return 0;
    }

    int EyerBuffer::ReadFromDisk(EyerString & path)
    {
        // TODO
        /*
        FILE * f = fopen(path.str, "rb");
        if(f == nullptr){
            return -1;
        }
        if(buf != nullptr){
            free(buf);
            buf = nullptr;
        }
        bufLen = 0;

        fseek(f, 0L, SEEK_END);
        bufLen = ftell(f);

        fseek(f, 0L, SEEK_SET);

        buf = (uint8_t *)malloc(bufLen);
        fread(buf, bufLen, 1, f);

        mallocTimes++;

        fclose(f);
         */
        return 0;
    }

    uint8_t * EyerBuffer::GetPtr() const
    {
        return buf;
    }

    int EyerBuffer::PrintfDebug()
    {
        EyerLog("Malloc Times: %d\n", mallocTimes);
        return 0;
    }
}
