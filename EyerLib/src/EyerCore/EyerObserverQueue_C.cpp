#include "EyerObserverQueue.h"
#include "EyerObserverQueue.hpp"

void *      observer_queue_init             ()
{
    Eyer::EyerObserverQueue<void *> * queue = new Eyer::EyerObserverQueue<void *>();
    return queue;
}

int         observer_queue_uninit           (void * _queue)
{
    Eyer::EyerObserverQueue<void *> * queue = (Eyer::EyerObserverQueue<void *> *)_queue;
    delete queue;
    return 0;
}

int         observer_queue_push             (void * _queue, void * content)
{
    Eyer::EyerObserverQueue<void *> * queue = (Eyer::EyerObserverQueue<void *> *)_queue;
    return queue->Push(content);
}

int         observer_queue_frontpop         (void * _queue, void * content)
{
    Eyer::EyerObserverQueue<void *> * queue = (Eyer::EyerObserverQueue<void *> *)_queue;
    return queue->FrontPop(content);
}

int         observer_queue_size             (void * _queue)
{
    Eyer::EyerObserverQueue<void *> * queue = (Eyer::EyerObserverQueue<void *> *)_queue;
    return queue->Size();
}