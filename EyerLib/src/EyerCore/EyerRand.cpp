#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "EyerRand.hpp"

namespace Eyer {
    int EyerRand::Rand(int x)
    {
        return (rand() * 1.0f / RAND_MAX) * x;
    }

    EyerString EyerRand::RandNumberStr(int length)
    {
        EyerString str;
        for(int i=0;i<length;i++){
            int num = 0;
            while(1){
                num = Rand(10);
                if(num <= 0){
                    continue;
                }
                if(num >= 10){
                    continue;
                }
                break;
            }
            str = str + EyerString::Number(num);
        }
        return str;
    }
}