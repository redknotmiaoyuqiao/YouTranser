#include "LoadingTimerThread.h"

#include <QDebug>

#include "EyerCore/EyerCore.hpp"

LoadingTimerThread::LoadingTimerThread()
{

}

LoadingTimerThread::~LoadingTimerThread()
{

}

void LoadingTimerThread::run()
{
    qDebug() << "LoadingTimerThread Start" << Qt::endl;

    Eyer::EyerTime::EyerSleepMilliseconds(2000);
    emit OnTimeout();

    qDebug() << "LoadingTimerThread End" << Qt::endl;
}
