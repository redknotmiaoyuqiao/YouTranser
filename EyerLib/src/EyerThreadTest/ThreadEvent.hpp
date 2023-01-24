#ifndef EYERLIB_THREADEVENT_HPP
#define EYERLIB_THREADEVENT_HPP

#include <gtest/gtest.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerThread/EyerThread.hpp"

class EyerThreadEventThread : public Eyer::EyerThread
{
public:
    std::mutex mtx;
    std::condition_variable cv;

    virtual void Run() override
    {
        while(!stopFlag){
            std::unique_lock <std::mutex> lck(mtx);
            while(!stopFlag && !eventLoopFlag){
                cv.wait(lck);
            }

            EventLoop();

            str += "1234567890";
        }
    }

    virtual int SetStopFlag() override
    {
        std::unique_lock <std::mutex> lck(mtx);
        stopFlag = 1;
        cv.notify_all();
        return 0;
    }

    virtual int SetStartEventLoopFlag() override
    {
        std::unique_lock <std::mutex> lck(mtx);
        eventLoopFlag = 1;
        cv.notify_all();
        return 0;
    }

    int AppendStr()
    {
        str += "abc";
        EyerLog("str: %d\n", strlen(str.c_str()));
        return 0;
    }

private:
    Eyer::EyerString str;
};

class MyEvent : public Eyer::EyerRunnable
{
public:
    EyerThreadEventThread * event = nullptr;

    MyEvent(EyerThreadEventThread * _event)
    {
        event = _event;
    }

    virtual void Run() override
    {
        event->AppendStr();
    }
};

TEST(EyerThread, EyerThreadEvent)
{

    EyerThreadEventThread thread;
    thread.Start();

    for(int i=0;i<1000;i++){
        Eyer::EyerTime::EyerSleepMilliseconds(5);

        MyEvent event(&thread);
        thread.PushEvent(&event);
        thread.StartEventLoop();
        thread.StopEventLoop();
        thread.ClearAllEvent();
    }

    thread.Stop();
}

#endif //EYERLIB_THREADEVENT_HPP
