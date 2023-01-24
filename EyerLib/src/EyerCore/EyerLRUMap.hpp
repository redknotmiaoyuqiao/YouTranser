#ifndef EYE_LIB_EYER_CORE_LRU_MAP_HPP
#define EYE_LIB_EYER_CORE_LRU_MAP_HPP

#include <mutex>
#include <map>
#include "EyerTime.hpp"

namespace Eyer
{

    template <typename T>
    class EyerLRUData
    {
    public:
        int hot = 0;
        long long time;
        T * t = nullptr;

        EyerLRUData(T * _t){
            t = _t;
            time = Eyer::EyerTime::GetTime();
        }

        ~EyerLRUData(){
            if(t != nullptr){
                delete t;
                t = nullptr;
            }
        }
    };

    template <typename K, typename V>
    class EyerLRUMap
    {
    public:
        EyerLRUMap(int maxSize = 100);
        ~EyerLRUMap();

        int Put(const K & k, V * & v);
        int Get(const K & k, V * & v);

        int Size();
    private:
        std::mutex mut;
        std::map<K, EyerLRUData<V> *> mapSet;

        int maxSize = 0;

        int LruRemoveHotless();
    };


    template <typename K, typename V>
    EyerLRUMap<K, V>::EyerLRUMap(int _maxSize)
    {
        maxSize = _maxSize;
    }

    template <typename K, typename V>
    EyerLRUMap<K, V>::~EyerLRUMap()
    {
        std::lock_guard<std::mutex> lg(mut);
        while(mapSet.size() > 0){
            LruRemoveHotless();
        }
    }

    template <typename K, typename V>
    int EyerLRUMap<K, V>::Put(const K & k, V * & v)
    {
        std::lock_guard<std::mutex> lg(mut);
        while(mapSet.size() >= maxSize){
            LruRemoveHotless();
        }

        EyerLRUData<V> * data = new EyerLRUData<V>(v);

        data->hot = 0;
        data->t = v;
        data->time = Eyer::EyerTime::GetTime();

        mapSet.insert(typename std::map<K, EyerLRUData<V> *>::value_type(k, data));
        return 0;
    }

    template <typename K, typename V>
    int EyerLRUMap<K, V>::Size()
    {
        std::lock_guard<std::mutex> lg(mut);
        return mapSet.size();
    }

    template <typename K, typename V>
    int EyerLRUMap<K, V>::Get(const K & k, V * & v)
    {
        typename std::map<K, EyerLRUData<V> *>::iterator iter;
        iter = mapSet.find(k);
        if(iter != mapSet.end()){
            EyerLRUData<V> * data = iter->second;
            data->hot++;
            data->time = Eyer::EyerTime::GetTime();
            v = data->t;

            return 0;
        }
        return -1;
    }


    template <typename K, typename V>
    int EyerLRUMap<K, V>::LruRemoveHotless()
    {
        long long time = -1;
        K k;
        typename std::map<K, EyerLRUData<V> *>::iterator iter;
        for(iter=mapSet.begin(); iter!=mapSet.end(); iter++) {
            if(time == -1){
                time = iter->second->time;
                k = iter->first;
            }
            if(time > iter->second->time){
                time = iter->second->time;
                k = iter->first;
            }
        }

        if(time >= 0){
            iter = mapSet.find(k);
            if(iter != mapSet.end()){
                EyerLRUData<V> * data = iter->second;
                delete data;
                mapSet.erase(iter);
            }
        }

        return 0;
    }

}

#endif
