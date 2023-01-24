#ifndef EYE_LIB_EYER_CORE_LOCK_QUEUE_HPP
#define EYE_LIB_EYER_CORE_LOCK_QUEUE_HPP

#include <mutex>
#include <queue>

namespace Eyer
{
    template<typename T>
    class EyerLockQueue {
    public:
        EyerLockQueue()
        {

        }

        ~EyerLockQueue()
        {
            std::lock_guard<std::mutex> lg(mut);
            while(queue.size() > 0){
                T * t = queue.front();
                queue.pop();
            }
        }

        int Push(T * t)
        {
            std::lock_guard<std::mutex> lg(mut);
            queue.push(t);
            return 0;
        }

        int Front(T ** t)
        {
            std::lock_guard<std::mutex> lg(mut);
            int ret = -1;

            if(queue.size() > 0){
                *t = queue.front();
                ret = 0;
            }

            return ret;
        }

        int FrontPop(T ** t)
        {
            std::lock_guard<std::mutex> lg(mut);
            int ret = -1;

            if(queue.size() > 0) {
                *t = queue.front();
                queue.pop();
                ret = 0;
            }

            return ret;
        }

        int Size()
        {
            std::lock_guard<std::mutex> lg(mut);
            int size = queue.size();
            return size;
        }
        
    private:
        std::mutex mut;
        std::queue<T *> queue;
    };
}



#endif //EYE_LIB_EYERAVQUEUE_HPP