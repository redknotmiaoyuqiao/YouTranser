#ifndef EYERLIB_EYERBUFFER_H
#define EYERLIB_EYERBUFFER_H

#ifdef __cplusplus
extern "C"{
#endif

    void *  buffer_init                 ();
    int     buffer_uninit               (void * buffer);

    int     buffer_append               (void * buffer, unsigned char * data, int data_len);

    int     buffer_get_size             (void * buffer);
    int     buffer_get_data             (void * buffer, unsigned char * data);

#ifdef __cplusplus
}
#endif

#endif //EYERLIB_EYERBUFFER_H
