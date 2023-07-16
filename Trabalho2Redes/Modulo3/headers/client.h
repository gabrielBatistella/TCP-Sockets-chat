#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "mkSocket.h"
#include "channel.h"

#define MAX_CHARS_IN_NICKNAME 50

using namespace std;

class Client {

    private: 
        string nickname;
        Socket *socket;
        Channel *channel;
        bool mute;
        bool adm;

    public:
        Client(string nickname, Socket *socket);
        Client(Socket *socket);

        string GetNickname();
        bool SetNickname(string nickname);
        Socket * GetSocket();
        Channel * GetChannel();
        void SetChannel(Channel *channel);
        bool IsMute();
        void SetMute(bool mute);
        bool IsAdm();
        void SetAdm(bool adm);

        ~Client();
};

#endif