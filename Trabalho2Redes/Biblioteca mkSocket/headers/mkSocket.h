#ifndef MKSOCKET_H
#define MKSOCKET_H

#include <string>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "util.h"

using namespace std;

class Socket {

    private:
        int id;
        sockaddr_in addr;

        Socket(int id, sockaddr_in addr);
        void Init(in_addr_t ip, in_port_t port);
        sockaddr_in CreateSocketAddr(in_addr_t ip, in_port_t port);

    public:
        Socket(string ip, int port);
        Socket(string ip);
        Socket(int port);
        Socket();

        bool Connect(string ip, int port, int timeout);
        void Listen(int queueSize);
        Socket * Accept();

        string Receive();
        void Send(string msgToSend);

        sockaddr_in GetAddr();
        string GetIP();
        int GetPort();

        ~Socket();
};

#endif