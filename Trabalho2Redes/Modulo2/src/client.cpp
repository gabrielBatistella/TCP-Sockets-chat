#include "../headers/client.h"

Client::Client(string nickname, Socket *socket) {
    this->nickname = nickname;
    this->socket = socket;
}

string Client::GetNickname() {
    return this->nickname;
}

Socket * Client::GetSocket() {
    return this->socket;
}
        
Client::~Client() {
    delete (this->socket);
}