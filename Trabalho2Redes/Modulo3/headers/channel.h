#ifndef CHANNEL_H
#define CHANNEL_H

#include <iostream>
#include <string>
#include <vector>
#include "client.h"

#define MAX_CHARS_IN_CHANNELNAME 200
#define DEFAULT_CHANNEL_NAME "~HOME"

using namespace std;

class Channel {

    private:
        string name;
        vector<Client *> clientsOnChannel;
        vector<string> clientsInvited;
        bool privateChannel = false;

        bool ValidateChannelName(string name);

    public:
        Channel(string name);
        
        string GetName();
        vector<Client *> GetClientsInChannel();

        bool IsPrivate();        
        void SetPrivate(bool privateChannel);

        bool IsClientInvited(string nickname);
        void InviteClient(string nickname);

        bool AddClient(Client *client);
        void RemoveClient(Client *client);
        Client * FindClientByName(string nickname);

        Client * ChooseNewAdm();
        bool IsClientOnChannel(Client *client);
        bool IsEmpty();
        int NumberOfClientsConnected();

        ~Channel();
};

#endif