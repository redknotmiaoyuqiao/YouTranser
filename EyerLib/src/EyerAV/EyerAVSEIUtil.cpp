#include "EyerAVSEIUtil.hpp"

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    EyerAVSEIUtil::EyerAVSEIUtil()
    {

    }

    EyerAVSEIUtil::~EyerAVSEIUtil()
    {

    }

    EyerBufferPlus EyerAVSEIUtil::GenSEINALU(uint8_t * msg, int msgLen)
    {
        EyerBufferPlus totleBuffer;

        EyerBufferPlus buffer;

        // 写入 NALU Header
        uint8_t nalu_header_num = 102;
        buffer.WriteBigEndian(nalu_header_num);

        // payloadType
        int payloadType = 5;

        uint8_t payload_type_num = payloadType;

        // 写入 payload_type
        buffer.WriteBigEndian(payload_type_num);

        // 写入 payload_size
        uint8_t payload_size_num = msgLen + 16;
        buffer.WriteBigEndian(payload_size_num);

        unsigned char uuid[] = { 0x54, 0x80, 0x83, 0x97, 0xf0, 0x23, 0x47, 0x4b, 0xb7, 0xf7, 0x4f, 0x32, 0xb5, 0x4e, 0x06, 0xac };
        // 写入 UUID
        for(int i=0;i<16;i++){
            buffer.WriteBigEndian(uuid[i]);
        }

        // 写入内容
        for(int i=0;i<msgLen;i++){
            buffer.WriteBigEndian(msg[i]);
        }

        // 写入拖尾
        uint8_t trailing_num = 0x00;
        buffer.WriteBigEndian(trailing_num);

        uint32_t size = buffer.GetBufferLen();
        totleBuffer.WriteBigEndian(size + 4);
        totleBuffer.WriteBuffer(buffer);

        return totleBuffer;
    }
}