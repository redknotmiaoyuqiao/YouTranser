#ifndef LOADINGTIMERTHREAD_H
#define LOADINGTIMERTHREAD_H

#include <QThread>

class LoadingTimerThread : public QThread
{
    Q_OBJECT
public:
    LoadingTimerThread();
    virtual ~LoadingTimerThread();

signals:
    void OnTimeout();

protected:
    virtual void run() override;
};

#endif // LOADINGTIMERTHREAD_H
