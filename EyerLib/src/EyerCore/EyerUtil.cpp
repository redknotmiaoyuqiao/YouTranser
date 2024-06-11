#include "EyerUtil.hpp"
#include "EyerMD5.hpp"

namespace Eyer
{
    uint64_t EyerUtil::EndianNtohll(uint64_t val)
    {
        uint64_t res;
        if(CheckCPU()){
            // 小端
            uint8_t * a = (uint8_t *)&val;
            res = (uint64_t)a[0] << 56 | (uint64_t)a[1] << 48 | (uint64_t)a[2] << 40 | (uint64_t)a[3] << 32 | (uint64_t)a[4] << 24 | (uint64_t)a[5] << 16 | (uint64_t)a[6] << 8 | a[7];
        }
        else{
            res = val;
        }
        return res;
    }

    uint32_t EyerUtil::EndianNtohl(uint32_t val)
    {
        uint32_t res;
        if(CheckCPU()){
            // 小端
            uint8_t * a = (uint8_t *)&val;
            res = (uint32_t)a[0] << 24 | (uint32_t)a[1] << 16 | (uint32_t)a[2] << 8 | a[3];
        }
        else{
            res = val;
        }
        return res;
    }

    uint16_t EyerUtil::EndianNtohs         (uint16_t val)
    {
        uint16_t res;
        if(CheckCPU()){
            // 小端
            uint8_t * a = (uint8_t *)&val;
            res = (uint16_t)a[0] << 8 | (uint16_t)a[1];
        }
        else{
            res = val;
        }
        return res;
    }




    uint64_t EyerUtil::EndianHtonll(uint64_t val)
    {
        uint64_t res;
        if(CheckCPU()){
            // 小端
            uint8_t * a = (uint8_t *)&val;
            res = (uint64_t)a[0] << 56 | (uint64_t)a[1] << 48 | (uint64_t)a[2] << 40 | (uint64_t)a[3] << 32 | (uint64_t)a[4] << 24 | (uint64_t)a[5] << 16 | (uint64_t)a[6] << 8 | (uint64_t)a[7];
        }
        else{
            res = val;
        }
        return res;
    }

    uint32_t EyerUtil::EndianHtonl         (uint32_t val)
    {
        uint32_t res;
        if(CheckCPU()){
            // 小端
            uint8_t * a = (uint8_t *)&val;
            res = (uint32_t)a[0] << 24 | (uint32_t)a[1] << 16 | (uint32_t)a[2] << 8 | (uint32_t)a[3];
        }
        else{
            res = val;
        }
        return res;
    }

    uint16_t EyerUtil::EndianHtons         (uint16_t val)
    {
        uint16_t res;
        if(CheckCPU()){
            // 小端
            uint8_t * a = (uint8_t *)&val;
            res = (uint16_t)a[0] << 8 | (uint16_t)a[1];
        }
        else{
            res = val;
        }
        return res;
    }

    bool EyerUtil::CheckCPU()
    {
        union w
        {
            int a;
            char b;
        }c;

        c.a = 1;
        return (c.b == 1);
    }

    EyerString EyerUtil::Md5(const EyerString & messgae)
    {
        return EyerString("");
    }

    EyerString EyerUtil::ReadText(const EyerString & path)
    {
        FILE * f = fopen(path.c_str(), "rb");
        if(f == nullptr){
            return "";
        }

        fseek(f, 0, SEEK_END);
        int len = ftell(f);
        fseek(f, 0, SEEK_SET);

        uint8_t * data = (uint8_t *)malloc(len + 1);
        int ret = fread(data, len, 1, f);

        data[len] = '\0';
        EyerString res(reinterpret_cast<const char *>(data));

        if(data != nullptr){
            free(data);
            data = nullptr;
        }

        if(f != nullptr) {
            fclose(f);
            f = nullptr;
        }

        return res;
    }
}