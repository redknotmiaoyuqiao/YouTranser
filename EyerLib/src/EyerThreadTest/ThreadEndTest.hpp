#ifndef EYERLIB_THREADENDTEST_HPP
#define EYERLIB_THREADENDTEST_HPP

#include <time.h>
#include <stdio.h>
#include <chrono>
#include <thread>

#include <gtest/gtest.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerThread/EyerThread.hpp"

class EndTestThread : public Eyer::EyerThread
{
public:
    std::mutex mtx;
    std::condition_variable cv;

    virtual void Run() override
    {
        EyerLog("EndTestThread Start\n");
        std::unique_lock <std::mutex> lck(mtx);
        while(1){
            while(!stopFlag){
                cv.wait(lck);
            }
            if(stopFlag){
                break;
            }
        }
        EyerLog("EndTestThread End\n");
    }

    virtual int SetStopFlag() override
    {
        std::unique_lock <std::mutex> lck(mtx);
        stopFlag = 1;
        cv.notify_all();
        return 0;
    }
};

TEST(EyerThread, EyerThreadEndTest)
{
    EndTestThread thread;
    thread.Start();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000 * 5));

    thread.Stop();
}

#endif //EYERLIB_THREADENDTEST_HPP
