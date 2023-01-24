#include "EyerSockaddr.hpp"
#include <stdio.h>

namespace Eyer
{
    EyerSockaddr::EyerSockaddr()
    {

    }

    EyerSockaddr::~EyerSockaddr()
    {

    }

    EyerSockaddr::EyerSockaddr(const EyerSockaddr & addr)
    {
        *this = addr;
    }

    EyerSockaddr & EyerSockaddr::operator = (const EyerSockaddr & _addr)
    {
        int len = sizeof(sockaddr_in);
        memcpy(&addr, &_addr.addr, len);
        return *this;
    }

    int EyerSockaddr::GetLen()
    {
        return sizeof(sockaddr_in);
    }

    void * EyerSockaddr::GetPtr()
    {
        return &addr;
    }

    int EyerSockaddr::PrintInfo()
    {
        printf("ip: %s\n", inet_ntoa(addr.sin_addr));
        printf("port: %d\n", ntohs(addr.sin_port));
        return 0;
    }
}