#ifndef	EYER_MAPElE_H
#define	EYER_MAPElE_H

#include <stdio.h>

namespace Eyer {

    template<typename K, typename V>
    class EyerMapEle
    {
    public:
        K key;
        V value;
        EyerMapEle<K, V> * leftMapEle;
        EyerMapEle<K, V> * rightMapEle;
    public:
        EyerMapEle<K, V>(K _key, V _value, EyerMapEle<K, V> * _leftMapEle = nullptr, EyerMapEle<K, V>* _rightMapEle = nullptr) {
            key = _key;
            value = _value;
            leftMapEle = _leftMapEle;
            rightMapEle = _rightMapEle;
        }
        ~EyerMapEle<K, V>() {

        }
    };
}

#endif
