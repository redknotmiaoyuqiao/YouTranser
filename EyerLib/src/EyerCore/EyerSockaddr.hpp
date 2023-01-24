#ifndef EYERLIB_EYERSOCKADDR_HPP
#define EYERLIB_EYERSOCKADDR_HPP

#ifdef _WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

#endif // _WIN32

namespace Eyer
{
    class EyerSockaddr {
    public:
        EyerSockaddr();
        ~EyerSockaddr();
        EyerSockaddr(const EyerSockaddr & addr);

        EyerSockaddr & operator = (const EyerSockaddr & addr);

        int GetLen();
        void * GetPtr();

        int PrintInfo();

    private:
        struct sockaddr_in addr;
    };
}

#endif //EYERLIB_EYERSOCKADDR_HPP
