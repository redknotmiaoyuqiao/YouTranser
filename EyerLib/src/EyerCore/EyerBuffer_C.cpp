#include "EyerBuffer.h"
#include "EyerBuffer.hpp"

void *  buffer_init                 ()
{
    Eyer::EyerBuffer * buffer = new Eyer::EyerBuffer();
    return (void *)buffer;
}

int     buffer_uninit               (void * _buffer)
{
    Eyer::EyerBuffer * buffer = (Eyer::EyerBuffer *)_buffer;
    delete buffer;
    return 0;
}

int     buffer_append               (void * _buffer, unsigned char * _data, int _data_len)
{
    Eyer::EyerBuffer * buffer = (Eyer::EyerBuffer *)_buffer;
    return buffer->Append(_data, _data_len);
}

int     buffer_get_size             (void * _buffer)
{
    Eyer::EyerBuffer * buffer = (Eyer::EyerBuffer *)_buffer;
    return buffer->GetLen();
}

int     buffer_get_data             (void * _buffer, unsigned char * _data)
{
    Eyer::EyerBuffer * buffer = (Eyer::EyerBuffer *)_buffer;
    return buffer->GetBuffer(_data);
}