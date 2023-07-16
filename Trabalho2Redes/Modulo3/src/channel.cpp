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

vector<Client *> Channel::GetClientsInChannel() {
    return this->clientsOnChannel;
}

bool Channel::IsPrivate() {
    return this->privateChannel;
}

void Channel::SetPrivate(bool privateChannel) {
    this->privateChannel = privateChannel;
}

bool Channel::IsClientInvited(string nickname) {
    for(vector<string>::iterator nick = this->clientsInvited.begin() ; nick != this->clientsInvited.end() ; nick++) {
        if((*nick) == nickname) {
            return true;
        }
    }
    return false;
}

void Channel::InviteClient(string nickname) {
    if(!IsClientInvited(nickname)) {
        this->clientsInvited.push_back(nickname);
    }
}

bool Channel::AddClient(Client *client) {
    if(IsClientOnChannel(client)) return true;
    if(IsPrivate() && !IsClientInvited(client->GetNickname())) return false;

    if(IsEmpty()) {
        client->SetAdm(true);
    }
    else {   
        client->SetAdm(false);
    }

    this->clientsOnChannel.push_back(client);
    client->SetChannel((void *) this);
    client->SetMute(false);
    return true;
}

void Channel::RemoveClient(Client *client) {
    if(!IsClientOnChannel(client)) return;
    
    bool removedAdm = false;
    for(vector<Client *>::iterator cli = this->clientsOnChannel.begin() ; cli != this->clientsOnChannel.end() ; cli++) {
        if((*cli) == client) {
            this->clientsOnChannel.erase(cli);

            client->SetChannel(NULL);
            client->SetAdm(false);
            client->SetMute(false);
        }
    }
}

Client * Channel::FindClientByName(string nickname) {
    for(vector<Client *>::iterator cli = this->clientsOnChannel.begin() ; cli != this->clientsOnChannel.end() ; cli++) {
        if((*cli)->GetNickname() == nickname) {
            return (*cli);
        }
    }
    return NULL;
}

Client * Channel::ChooseNewAdm() {
    if(IsEmpty()) return NULL;

    for(vector<Client *>::iterator cli = this->clientsOnChannel.begin() ; cli != this->clientsOnChannel.end() ; cli++) {
        if((*cli)->IsAdm()) {
            return NULL;
        }
    }

    Client *newAdm = clientsOnChannel.at(0);
    newAdm->SetAdm(true);
    return newAdm;
}

bool Channel::IsClientOnChannel(Client *client) {
    for(vector<Client *>::iterator cli = this->clientsOnChannel.begin() ; cli != this->clientsOnChannel.end() ; cli++) {
        if((*cli) == client) {
            return true;
        }
    }
    return false;
}

bool Channel::IsEmpty() {
    return this->clientsOnChannel.size() == 0;
}

int Channel::NumberOfClientsConnected() {
    return this->clientsOnChannel.size();
}

Channel::~Channel() {
    this->clientsOnChannel.clear();
    this->clientsInvited.clear();
}