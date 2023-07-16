#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "mkSocket.h"

#define MAX_CHARS_IN_NICKNAME 50

using namespace std;

class Client {

    private: 
        string nickname;
        Socket *socket;
        void *channel;
        bool mute;
        bool adm;

    public:
        Client(string nickname, Socket *socket);
        Client(Socket *socket);

        string GetNickname();
        bool SetNickname(string nickname);
        Socket * GetSocket();
        void * GetChannel();
        void SetChannel(void *channel);
        bool IsMute();
        void SetMute(bool mute);
        bool IsAdm();
        void SetAdm(bool adm);

        ~Client();
};

#endif