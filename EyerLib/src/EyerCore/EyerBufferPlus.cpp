#include "EyerBufferPlus.hpp"
#include "EyerUtil.hpp"

#include <stdint.h>

namespace Eyer
{
    EyerBufferPlus::EyerBufferPlus(EyerBufferPlusCallback * _callback)
    {
        callback = _callback;
    }

    EyerBufferPlus::~EyerBufferPlus()
    {

    }

    EyerBufferPlus::EyerBufferPlus(const EyerBufferPlus & bufferPlus)
    {
        *this = bufferPlus;
    }

    EyerBufferPlus & EyerBufferPlus::operator = (const EyerBufferPlus & bufferPlus)
    {
        buffer = bufferPlus.buffer;
        callback = bufferPlus.callback;
        len = bufferPlus.len;
        return *this;
    }



    uint64_t EyerBufferPlus::ReadBigEndian_uint64(int &offset) {
        ReadData(sizeof(uint64_t));

        uint64_t val_net;
        buffer.CutOff((uint8_t *) &val_net, sizeof(uint64_t));

        offset += sizeof(uint64_t);

        return EyerUtil::EndianNtohll(val_net);
    }

    uint32_t EyerBufferPlus::ReadBigEndian_uint32(int &offset) {
        ReadData(sizeof(uint32_t));

        uint32_t val_net;
        buffer.CutOff((uint8_t *) &val_net, sizeof(uint32_t));

        offset += sizeof(uint32_t);

        return EyerUtil::EndianNtohl(val_net);
    }

    uint16_t EyerBufferPlus::ReadBigEndian_uint16(int &offset) {
        ReadData(sizeof(uint16_t));

        uint16_t val_net;
        buffer.CutOff((uint8_t *) &val_net, sizeof(uint16_t));

        offset += sizeof(uint16_t);

        return EyerUtil::EndianNtohs(val_net);
    }

    uint8_t  EyerBufferPlus::ReadBigEndian_uint8 (int & offset)
    {
        ReadData(sizeof(uint8_t));

        uint8_t val_net;
        buffer.CutOff((uint8_t *) &val_net, sizeof(uint8_t));

        offset += sizeof(uint8_t);

        return val_net;
    }







    int64_t EyerBufferPlus::ReadBigEndian_int64(int & offset)
    {
        ReadData(sizeof(int64_t));

        int64_t val_net;
        buffer.CutOff((uint8_t *) &val_net, sizeof(int64_t));

        offset += sizeof(int64_t);

        return EyerUtil::EndianNtohll(val_net);
    }

    int32_t EyerBufferPlus::ReadBigEndian_int32(int & offset)
    {
        ReadData(sizeof(int32_t));

        int32_t val_net;
        buffer.CutOff((uint8_t *) &val_net, sizeof(int32_t));

        offset += sizeof(int32_t);

        return EyerUtil::EndianNtohl(val_net);
    }

    int16_t EyerBufferPlus::ReadBigEndian_int16(int & offset)
    {
        ReadData(sizeof(int16_t));

        int16_t val_net;
        buffer.CutOff((uint8_t *) &val_net, sizeof(int16_t));

        offset += sizeof(int16_t);

        return EyerUtil::EndianNtohs(val_net);
    }





    uint32_t EyerBufferPlus::Read_uint32(int & offset)
    {
        ReadData(sizeof(int32_t));

        int32_t val_net;
        buffer.CutOff((uint8_t *) &val_net, sizeof(int32_t));

        offset += sizeof(int32_t);

        return val_net;
    }




    int EyerBufferPlus::WriteBigEndian(uint64_t val)
    {
        uint64_t net_val = EyerUtil::EndianHtonll(val);
        buffer.Append((uint8_t *)&net_val, sizeof(uint64_t));

        WriteData();
        return sizeof(uint64_t);
    }

    int EyerBufferPlus::WriteBigEndian(uint32_t val)
    {
        uint32_t net_val = EyerUtil::EndianHtonl(val);
        buffer.Append((uint8_t *)&net_val, sizeof(uint32_t));

        WriteData();
        return sizeof(uint32_t);
    }

    int EyerBufferPlus::WriteBigEndian(uint16_t val)
    {
        uint16_t net_val = EyerUtil::EndianHtons(val);
        buffer.Append((uint8_t *)&net_val, sizeof(uint16_t));

        WriteData();
        return sizeof(uint16_t);
    }

    int EyerBufferPlus::WriteBigEndian(uint8_t  val)
    {
        buffer.Append((uint8_t *)&val, sizeof(uint8_t));
        WriteData();
        return sizeof(uint8_t);
    }



    int EyerBufferPlus::WriteBigEndian(int64_t val)
    {
        int64_t net_val = EyerUtil::EndianHtonll(val);
        buffer.Append((uint8_t *)&net_val, sizeof(int64_t));
        WriteData();
        return sizeof(int64_t);
    }

    int EyerBufferPlus::WriteBigEndian(int32_t val)
    {
        int32_t net_val = EyerUtil::EndianHtonl(val);
        buffer.Append((uint8_t *)&net_val, sizeof(int32_t));
        WriteData();
        return sizeof(int32_t);
    }

    int EyerBufferPlus::WriteBigEndian(int16_t val)
    {
        int16_t net_val = EyerUtil::EndianHtons(val);
        buffer.Append((uint8_t *)&net_val, sizeof(int16_t));
        WriteData();
        return sizeof(int16_t);
    }

    int EyerBufferPlus::WriteBigEndian(int8_t  val)
    {
        buffer.Append((uint8_t *)&val, sizeof(int8_t));
        WriteData();
        return sizeof(int8_t);
    }

    int EyerBufferPlus::Write(uint32_t val)
    {
        buffer.Append((uint8_t *)&val, sizeof(uint32_t));

        WriteData();
        return sizeof(uint32_t);
    }


    int EyerBufferPlus::ReadBuffer(EyerBuffer & _buffer, int size)
    {
        ReadData(size);
        return buffer.CutOff(_buffer, size);
    }

    int EyerBufferPlus::WriteBuffer(EyerBuffer & _buffer)
    {
        int ret = buffer.Append(_buffer);
        WriteData();
        return ret;
    }

    int EyerBufferPlus::WriteBuffer(EyerBufferPlus & bufferPlus)
    {
        int ret = buffer.Append(bufferPlus.buffer);
        WriteData();
        return ret;
    }

    int EyerBufferPlus::GetBufferLen()
    {
        return buffer.GetLen();
    }

    uint64_t EyerBufferPlus::GetLen()
    {
        if(len == 0){
            if(callback != nullptr){
                len = callback->GetLen();
            }
        }
        return len;
    }



    int EyerBufferPlus::ReadData(int needSize)
    {
        if(buffer.GetLen() >= needSize) {
            return 0;
        }

        int size = needSize - buffer.GetLen();

        if(size > 0){
            if(callback != nullptr){
                uint8_t * buf = (uint8_t *)malloc(size);

                int ret = callback->ReadBuffer(buf, size);

                if(ret > 0){
                    buffer.Append(buf, ret);
                }

                free(buf);

                return ret;
            }
        }
        return 0;
    }

    int EyerBufferPlus::WriteData()
    {
        if(callback != nullptr){
            callback->WriteBuffer(buffer);
        }
        return 0;
    }
}
