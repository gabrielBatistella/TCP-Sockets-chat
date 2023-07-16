#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include "mkSocket.h"
#include "client.h"

using namespace std;

class Server {

    private:
        Socket *listenerSocket;
        vector<Client *> clientsConnected;
        int maxClients;
        mutex m_cli, m_log;

        int lastId = 0;

        Client * AddClient(Socket *clientSocket);
        void RemoveClient(Client *clientToRemove);

        string GenerateNewNickname();

        void Log(string msg);
        void SendToAll(string msg);
        void SendToAll(string msg, Client *sender);
        void SendToClient(string msg, Client *receiver);
        void SendToClient(string msg, Client *receiver, Client *sender);

        void ExecuteCommand(string commandReceived, Client *sender);
        void CommandPing(Client *sender);
        void CommandInvalid(Client *sender);

    protected:
        void ListenForClients();
        void HandleClient(Client *client);

    public:
        Server(string ip, int port, int maxClients);
        Server(string ip, int maxClients);
        Server(int port, int maxClients);
        Server(int maxClients);

        void Start();

        ~Server();
};

#endif