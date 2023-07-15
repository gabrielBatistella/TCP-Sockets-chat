#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "mkSocket.h"

using namespace std;

class Client {

    private: 
        string nickname;
        Socket *socket;

    public:
        Client(string nickname, Socket *socket);

        string GetNickname();
        Socket * GetSocket();

        ~Client();
};

#endif