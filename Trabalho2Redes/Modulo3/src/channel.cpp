#include "../headers/channel.h"

bool Channel::ValidateChannelName(string name) {
    bool nameLength = name.size() <= MAX_CHARS_IN_CHANNELNAME;
    bool startChar = name.at(0) == '&' || name.at(0) == '#';
    bool prohibitedChar = name.find(' ') == string::npos && name.find(',') == string::npos && name.find(7) == string::npos;
    return nameLength && startChar && prohibitedChar;
}

Channel::Channel(string name) {
    if(ValidateChannelName(name)) {
        this->name = name;
        this->privateChannel = false;
    }
    else {
        throw invalid_argument("Nome de canal inválido");
    }
}

string Channel::GetName() {
    return this->name;
}

bool Channel::IsPrivate() {
    return this->privateChannel;
}

void Channel::SetPrivate(bool privateChannel) {
    this->privateChannel = privateChannel;
}

bool Channel::IsClientInvited(string nickname) {
    for(vector<string>::iterator nick = this->invitedClients.begin() ; nick != this->invitedClients.end() ; nick++) {
        if((*nick) == nickname) {
            return true;
        }
    }
    return false;
}

void Channel::InviteClient(string nickname) {
    if(!IsClientInvited(nickname)) {
        this->invitedClients.push_back(nickname);
    }
}

Channel::~Channel() {
    this->invitedClients.clear();
}