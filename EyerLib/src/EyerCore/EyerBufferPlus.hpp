#ifndef EYERLIB_EYERBUFFERPLUS_HPP
#define EYERLIB_EYERBUFFERPLUS_HPP

#include "EyerString.hpp"
#include "EyerBuffer.hpp"

#include <stdio.h>
#include <stdlib.h>

#include "EyerBufferPlusCallback.hpp"

namespace Eyer
{
    class EyerBufferPlus {
    public:
        EyerBufferPlus(EyerBufferPlusCallback * callback = nullptr);
        ~EyerBufferPlus();

        EyerBufferPlus(const EyerBufferPlus & bufferPlus);
        EyerBufferPlus & operator = (const EyerBufferPlus & bufferPlus);

        uint64_t ReadBigEndian_uint64(int & offset);
        uint32_t ReadBigEndian_uint32(int & offset);
        uint16_t ReadBigEndian_uint16(int & offset);
        uint8_t  ReadBigEndian_uint8 (int & offset);

        int64_t ReadBigEndian_int64(int & offset);
        int32_t ReadBigEndian_int32(int & offset);
        int16_t ReadBigEndian_int16(int & offset);

        uint32_t Read_uint32(int & offset);


        int WriteBigEndian(uint64_t val);
        int WriteBigEndian(uint32_t val);
        int WriteBigEndian(uint16_t val);
        int WriteBigEndian(uint8_t  val);

        int WriteBigEndian(int64_t val);
        int WriteBigEndian(int32_t val);
        int WriteBigEndian(int16_t val);
        int WriteBigEndian(int8_t  val);

        int Write(uint32_t val);



        int GetBufferLen();
        uint64_t GetLen();

        int ReadBuffer(EyerBuffer & buffer, int size);
        int WriteBuffer(EyerBuffer & buffer);
        int WriteBuffer(EyerBufferPlus & bufferPlus);

    private:
        EyerBuffer buffer;

        EyerBufferPlusCallback * callback = nullptr;

        int ReadData(int fragmentSize = 1024);
        int WriteData();

        uint64_t len = 0;
    };
}

#endif //EYERLIB_EYERBUFFERPLUS_HPP
