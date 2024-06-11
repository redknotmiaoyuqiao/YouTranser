#ifndef EYERLIB_EYERUTIL_HPP
#define EYERLIB_EYERUTIL_HPP

#include <stdint.h>
#include "EyerCore.hpp"

namespace Eyer
{
    class EyerUtil {
    public:
        static uint64_t EndianNtohll        (uint64_t val);
        static uint32_t EndianNtohl         (uint32_t val);
        static uint16_t EndianNtohs         (uint16_t val);

        static uint64_t EndianHtonll        (uint64_t val);
        static uint32_t EndianHtonl         (uint32_t val);
        static uint16_t EndianHtons         (uint16_t val);

        template<typename T>
        static int PrintBin(T & n)
        {
            int l = sizeof(n) * 8;//总位数。
            int i;
            for(i = l-1; i >= 0; i --){
                if(n & (1 << i)) {
                    break;
                }
            }
            EyerString str = "";
            for(;i>=0; i --) {
                str += EyerString::Number((n & (1 << i)) != 0);
            }
            EyerLog("%s\n", str.c_str());
            return 0;
        }

        static bool CheckCPU();

        static EyerString Md5(const EyerString & messgae);

        static EyerString ReadText(const EyerString & path);
    };
}

#endif //EYERLIB_EYERUTIL_HPP
