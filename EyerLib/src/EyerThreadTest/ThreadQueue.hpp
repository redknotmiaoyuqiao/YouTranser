#ifndef EYERLIB_THREADQUEUE_HPP
#define EYERLIB_THREADQUEUE_HPP

#include <time.h>
#include <stdio.h>
#include <chrono>
#include <thread>

#include <gtest/gtest.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerThread/EyerThread.hpp"

std::mutex mtx;
std::condition_variable cv;
Eyer::EyerObserverQueue<std::string> queue;

class EndQueueProducterThread : public Eyer::EyerThread
{
public:
    virtual void Run() override
    {
        EyerLog("EndQueueProducterThread Start\n");
        std::unique_lock <std::mutex> lck(mtx);
        while(1){
            while(!stopFlag && queue.SizeLock() > 10){
                cv.wait(lck);
            }

            queue.Lock();
            int size = queue.Size();
            if(size <= 10){
                std::string a = "abcabc";
                queue.Push(a);
                cv.notify_all();
            }
            queue.Unlock();

            if(stopFlag){
                break;
            }
        }
        EyerLog("EndQueueProducterThread End\n");
    }

    virtual int SetStopFlag() override
    {
        std::unique_lock <std::mutex> lck(mtx);
        stopFlag = 1;
        cv.notify_all();
        return 0;
    }
};

class EndQueueConsumerThread : public Eyer::EyerThread
{
public:
    virtual void Run() override
    {
        int index = 0;
        EyerLog("EndQueueConsumerThread Start\n");

        std::unique_lock<std::mutex> lck(mtx);
        while(1){
            while(!stopFlag && queue.SizeLock() <= 0) {
                cv.wait(lck);
            }

            queue.Lock();
            int size = queue.Size();
            if(size > 0){
                std::string a;
                queue.FrontPop(a);
                index++;

                if(index % 1000000 == 0){
                    EyerLog("index: %d\n", index);
                }
                cv.notify_all();
            }
            queue.Unlock();

            if(stopFlag){
                break;
            }
        }
        EyerLog("EndQueueConsumerThread End\n");
    }

    virtual int SetStopFlag() override
    {
        std::unique_lock <std::mutex> lck(mtx);
        stopFlag = 1;
        cv.notify_all();
        return 0;
    }
};


TEST(EyerThread, EyerThreadQueueTest)
{
    for(int i=0;i<5;i++){
        EndQueueProducterThread productThread;
        productThread.Start();
        EndQueueConsumerThread consumerThread;
        consumerThread.Start();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000 * 6));

        consumerThread.Stop();
        productThread.Stop();
    }
}

#endif //EYERLIB_THREADQUEUE_HPP
