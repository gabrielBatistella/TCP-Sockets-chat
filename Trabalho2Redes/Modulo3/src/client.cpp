#include "../headers/client.h"

Client::Client(string nickname, Socket *socket) {
    this->nickname = nickname;
    this->socket = socket;
    this->channel = NULL;
    this->mute = false;
    this->adm = false;
}

Client::Client(Socket *socket) {
    this->nickname = "";
    this->socket = socket;
    this->channel = NULL;
    this->mute = false;
    this->adm = false;
}

string Client::GetNickname() {
    return this->nickname;
}

bool Client::SetNickname(string nickname) {
    if(nickname.size() <= MAX_CHARS_IN_NICKNAME && nickname != "") {
        this->nickname = nickname;
        return true;
    }
    else {
        return false;
    }
}

Socket * Client::GetSocket() {
    return this->socket;
}

void * Client::GetChannel() {
    return this->channel;
}

void Client::SetChannel(void *channel) {
    this->channel = channel;
}

bool Client::IsMute() {
    return this->mute;
}

void Client::SetMute(bool mute) {
    this->mute = mute;
}

bool Client::IsAdm() {
    return this->adm;
}

void Client::SetAdm(bool adm) {
    this->adm = adm;
}
        
Client::~Client() {
    delete (this->socket);
}