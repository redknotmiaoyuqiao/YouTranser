#include "EyerThread.hpp"

#include <functional>

#include <time.h>
#include <stdio.h>
#include <chrono>
#include <thread>

namespace Eyer
{
    EyerThread::EyerThread()
    {

    }

    EyerThread::~EyerThread()
    {
        Stop();

        if(startAndWaitEventLoopPromise != nullptr){
            delete startAndWaitEventLoopPromise;
            startAndWaitEventLoopPromise = nullptr;
        }
        if(waitForStartEventLoopPromise != nullptr){
            delete waitForStartEventLoopPromise;
            waitForStartEventLoopPromise = nullptr;
        }
        if(waitForFinishEventLoopPromise != nullptr){
            delete waitForFinishEventLoopPromise;
            waitForFinishEventLoopPromise = nullptr;
        }
        if(stopAndWaitEventLoopPromise != nullptr){
            delete stopAndWaitEventLoopPromise;
            stopAndWaitEventLoopPromise = nullptr;
        }
        if(stopOkAndWaitEventLoopPromise != nullptr){
            delete stopOkAndWaitEventLoopPromise;
            stopOkAndWaitEventLoopPromise = nullptr;
        }
    }

    int EyerThread::Start()
    {
        if(t != nullptr){
            return -1;
        }

        stopFlag = 0;
        t = new std::thread(&EyerThread::Run, this);

        return 0;
    }

    int EyerThread::Stop()
    {
        if(t == nullptr){
            return -1;
        }

        SetStopFlag();

        if(t != nullptr){
            t->join();
            delete t;
            t = nullptr;
        }
        stopFlag = 0;

        return 0;
    }


    int EyerThread::EventLoop()
    {
        if(eventLoopFlag){
            if(startAndWaitEventLoopPromise != nullptr){
                startAndWaitEventLoopPromise->set_value();
            }

            // 等待开始执行
            if(waitForStartEventLoopPromise != nullptr) {
                waitForStartEventLoopPromise->get_future().get();
            }

            for(int i=0;i<eventList.size();i++){
                eventList[i]->Run();
            }

            if(waitForFinishEventLoopPromise != nullptr){
                waitForFinishEventLoopPromise->set_value();
            }

            eventLoopFlag = 0;

            if(stopAndWaitEventLoopPromise != nullptr){
                stopAndWaitEventLoopPromise->get_future().get();
            }
            if(stopOkAndWaitEventLoopPromise != nullptr){
                stopOkAndWaitEventLoopPromise->set_value();
            }
        }
        return 0;
    }

    int EyerThread::StartEventLoop()
    {
        StartAndWaitEventLoop();
        EnterEventLoop();
        return 0;
    }

    int EyerThread::StopEventLoop()
    {
        WaitForFinishEventLoop();
        QuitEventLoop();
        return 0;
    }

    int EyerThread::StartAndWaitEventLoop()
    {
        startAndWaitEventLoopPromise    = new std::promise<void>();
        waitForStartEventLoopPromise    = new std::promise<void>();
        waitForFinishEventLoopPromise   = new std::promise<void>();
        stopAndWaitEventLoopPromise     = new std::promise<void>();
        stopOkAndWaitEventLoopPromise   = new std::promise<void>();

        SetStartEventLoopFlag();
        startAndWaitEventLoopPromise->get_future().get();
        return 0;
    }

    int EyerThread::EnterEventLoop()
    {
        if(waitForStartEventLoopPromise != nullptr){
            waitForStartEventLoopPromise->set_value();
        }
        return 0;
    }

    int EyerThread::WaitForFinishEventLoop()
    {
        if(waitForFinishEventLoopPromise != nullptr){
            waitForFinishEventLoopPromise->get_future().get();
        }
        return 0;
    }

    int EyerThread::QuitEventLoop()
    {
        if(stopAndWaitEventLoopPromise != nullptr){
            stopAndWaitEventLoopPromise->set_value();
        }
        if(stopOkAndWaitEventLoopPromise != nullptr){
            stopOkAndWaitEventLoopPromise->get_future().get();
        }


        if(startAndWaitEventLoopPromise != nullptr){
            delete startAndWaitEventLoopPromise;
            startAndWaitEventLoopPromise = nullptr;
        }
        if(waitForStartEventLoopPromise != nullptr){
            delete waitForStartEventLoopPromise;
            waitForStartEventLoopPromise = nullptr;
        }
        if(waitForFinishEventLoopPromise != nullptr){
            delete waitForFinishEventLoopPromise;
            waitForFinishEventLoopPromise = nullptr;
        }
        if(stopAndWaitEventLoopPromise != nullptr){
            delete stopAndWaitEventLoopPromise;
            stopAndWaitEventLoopPromise = nullptr;
        }
        if(stopOkAndWaitEventLoopPromise != nullptr){
            delete stopOkAndWaitEventLoopPromise;
            stopOkAndWaitEventLoopPromise = nullptr;
        }
        return 0;
    }

    int EyerThread::PushEvent(EyerRunnable * runnable)
    {
        eventList.push_back(runnable);
        return 0;
    }

    int EyerThread::ClearAllEvent()
    {
        eventList.clear();
        return 0;
    }

    int EyerThread::SetStopFlag()
    {
        stopFlag = 1;
        return 0;
    }

    int EyerThread::SetStartEventLoopFlag()
    {
        eventLoopFlag = 1;
        return 0;
    }
}