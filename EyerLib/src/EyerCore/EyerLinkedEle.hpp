#ifndef	EYER_LINKEDElE_H
#define	EYER_LINKEDElE_H

#include <stdio.h>

namespace Eyer {
    
    template <typename T>
    class EyerLinkedEle
    {
    public:
        T data;
        EyerLinkedEle<T> * next;
    public:
        EyerLinkedEle<T>(T _data, EyerLinkedEle<T> * _next = nullptr){
            data = _data;
            next = _next;
        }
        ~EyerLinkedEle<T>(){
            
        }
    };  
}

#endif