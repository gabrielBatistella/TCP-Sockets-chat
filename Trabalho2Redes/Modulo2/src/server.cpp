#include "../headers/server.h"

Client * Server::AddClient(Socket *clientSocket) {
    if((int)(this->clientsConnected.size()) >= this->maxClients) {
        return NULL;
    }
    
    string nickname = GenerateNewNickname();
    Client *client = new Client(nickname, clientSocket);

    m_cli.lock();
    this->clientsConnected.push_back(client);
    m_cli.unlock();
    
    thread clientHandling([] (Server *server, Client *client) {server->HandleClient(client);}, this, client);
    clientHandling.detach();
    
    return client;
}

void Server::RemoveClient(Client *clientToRemove) {
    m_cli.lock();
    for(vector<Client *>::iterator cli = this->clientsConnected.begin() ; cli != this->clientsConnected.end() ; cli++) {
        if((*cli) == clientToRemove) {
            delete (*cli);
            this->clientsConnected.erase(cli);
            break;
        }
    }
    m_cli.unlock();
}

string Server::GenerateNewNickname() {
    this->lastId += 1;
    string nickname = "client_";
    nickname = nickname + to_string(this->lastId);
    return nickname;
}

void Server::Log(string msg) {
    m_log.lock();
    cout << "-> " << msg << endl;
    m_log.unlock();
}

void Server::SendToAll(string msg) {
    Log("(server) " + msg);
    string msgToSend = msg + " <<<<<";

    for(vector<Client *>::iterator cli = this->clientsConnected.begin() ; cli != this->clientsConnected.end() ; cli++) {
        SendToClient(msgToSend, *cli);
    }
}

void Server::SendToAll(string msg, Client *sender) {
    Log("(" + sender->GetNickname() + ") " + msg);
    string msgToSend = msg;

    for(vector<Client *>::iterator cli = this->clientsConnected.begin() ; cli != this->clientsConnected.end() ; cli++) {
        SendToClient(msgToSend, *cli, sender);
    }
}

void Server::SendToClient(string msg, Client *receiver) {
    string msgToSend = ">>>>> " + msg;
    
    m_cli.lock();
    receiver->GetSocket()->Send(msgToSend);
    m_cli.unlock();
}

void Server::SendToClient(string msg, Client *receiver, Client *sender) {
    string msgToSend;
    if(sender == receiver) {
        msgToSend = sender->GetNickname() + " (You) : " + msg;
    }  
    else {
        msgToSend = sender->GetNickname() + " : " + msg;
    }
    
    m_cli.lock();
    receiver->GetSocket()->Send(msgToSend);
    m_cli.unlock();
}

void Server::ExecuteCommand(string commandReceived, Client *sender) {
    string command;
    int argc;
    char **argv;
    getCommandAndArgs(commandReceived, &command, &argc, &argv);

    if(command == "/ping") {
        CommandPing(sender);
    }
    else {
        CommandInvalid(sender);
    }

    freeArgvMemory(argc, &argv);
}

void Server::CommandPing(Client *sender) {
    Log(sender->GetNickname() + " enviou um ping");
    SendToClient("pong", sender);
    Log("servidor respondeu com um pong");
}

void Server::CommandInvalid(Client *sender) {
    SendToClient("Comando inválido!", sender);
}

void Server::ListenForClients() {
    while(true) {
        Socket *socket = this->listenerSocket->Accept();
        Client *newClient = AddClient(socket);
        if(newClient == NULL) {
            delete socket;
        }
        else {
            SendToAll(newClient->GetNickname() + " entrou no servidor");
        }
    }
}

void Server::HandleClient(Client *client) {
    while(true) {
        string receiveMsg = client->GetSocket()->Receive();
        if(receiveMsg == "") {
            SendToAll(client->GetNickname() + " saiu do servidor");
            RemoveClient(client);
            return;
        }
        else if(receiveMsg.at(0) == '/') {
            ExecuteCommand(receiveMsg, client);
        } 
        else {
            SendToAll(receiveMsg, client);
        }
    }
}

Server::Server(string ip, int port, int maxClients) {
    this->listenerSocket = new Socket(ip, port);
    this->maxClients = maxClients;
}

Server::Server(string ip, int maxClients) {
    this->listenerSocket = new Socket(ip);
    this->maxClients = maxClients;
}

Server::Server(int port, int maxClients) {
    this->listenerSocket = new Socket(port);
    this->maxClients = maxClients;
}

Server::Server(int maxClients) {
    this->listenerSocket = new Socket();
    this->maxClients = maxClients;
}

void Server::Start() {
    this->listenerSocket->Listen(SOMAXCONN);
    cout << "Servidor Aberto. Esperando conexões na porta " << this->listenerSocket->GetPort() << endl;

    thread listeningThread([] (Server *server) {server->ListenForClients();}, this);
    listeningThread.detach();
}

Server::~Server() {
    delete listenerSocket;

    m_cli.lock();
    for(vector<Client *>::iterator cli = this->clientsConnected.begin() ; cli != this->clientsConnected.end() ; cli++) {
        delete (*cli);
    }
    this->clientsConnected.clear();
    m_cli.unlock();
}
