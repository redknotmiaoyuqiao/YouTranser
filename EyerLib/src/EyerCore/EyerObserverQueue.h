#ifndef EYERLIB_EYEROBSERVERQUEUE_H
#define EYERLIB_EYEROBSERVERQUEUE_H

#ifdef __cplusplus
extern "C"{
#endif

    void *      observer_queue_init             ();
    int         observer_queue_uninit           (void * queue);

    int         observer_queue_push             (void * queue, void * content);
    int         observer_queue_frontpop         (void * queue, void * content);

    int         observer_queue_size             (void * queue);

#ifdef __cplusplus
}
#endif

#endif //EYERLIB_EYEROBSERVERQUEUE_H
