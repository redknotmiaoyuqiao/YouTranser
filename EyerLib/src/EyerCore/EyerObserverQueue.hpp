#ifndef EYERLIB_EYEROBSERVERQUEUE_HPP
#define EYERLIB_EYEROBSERVERQUEUE_HPP

#include <mutex>
#include <queue>
#include "EyerSubject.hpp"

namespace Eyer
{
    template<typename T>
    class EyerObserverQueue : public EyerSubject {
    public:
        EyerObserverQueue()
        {

        }

        ~EyerObserverQueue()
        {
            std::lock_guard<std::mutex> lg(mtx);
            while(queue.size() > 0){
                T t = queue.front();
                queue.pop();
            }
        }

        int Lock()
        {
            mtx.lock();
            return 0;
        }

        int Unlock()
        {
            mtx.unlock();
            return 0;
        }

        int Push(const T & t)
        {
            queue.push(t);
            NotifyObserver();
            return 0;
        }

        int PushLock(const T & t)
        {
            std::lock_guard<std::mutex> lg(mtx);
            return Push(t);
        }

        int Front(T & t)
        {
            int ret = -1;

            if(queue.size() > 0){
                t = queue.front();
                ret = 0;
            }

            return ret;
        }

        int FrontLock(T & t)
        {
            std::lock_guard<std::mutex> lg(mtx);
            return Front(t);
        }

        int FrontPop(T & t)
        {
            int ret = -1;
            if(queue.size() > 0) {
                t = queue.front();
                queue.pop();
                ret = 0;
                NotifyObserver();
            }

            return ret;
        }

        T FrontPop(){
            T t;
            if(queue.size() > 0) {
                t = queue.front();
                queue.pop();
                NotifyObserver();
            }
            return t;
        }

        int FrontPopLock(T & t)
        {
            std::lock_guard<std::mutex> lg(mtx);
            return FrontPop(t);
        }

        T FrontPopLock(){
            std::lock_guard<std::mutex> lg(mtx);
            return FrontPop();
        }

        int Size()
        {
            int size = queue.size();
            return size;
        }

        int SizeLock()
        {
            std::lock_guard<std::mutex> lg(mtx);
            return Size();
        }

    private:
        std::mutex mtx;
        std::queue<T> queue;
    };
}


#endif //EYERLIB_EYEROBSERVERQUEUE_HPP
