#ifndef CHANNEL_H
#define CHANNEL_H

#include <iostream>
#include <string>
#include <vector>

#define MAX_CHARS_IN_CHANNELNAME 200

using namespace std;

class Channel {

    private:
        string name;
        vector<string> invitedClients;
        bool privateChannel = false;

        bool ValidateChannelName(string name);

    public:
        Channel(string name);
        
        string GetName();
        
        bool IsPrivate();        
        void SetPrivate(bool privateChannel);

        bool IsClientInvited(string nickname);
        void InviteClient(string nickname);

        ~Channel();
};

#endif