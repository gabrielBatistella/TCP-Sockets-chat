#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include "mkSocket.h"
#include "client.h"
#include "channel.h"

using namespace std;

class Server {

    private:
        Socket *listenerSocket;
        map<Channel *, vector<Client *> *> clientsConnected;
        int amountClients = 0;
        int maxClients;
        mutex m_cli, m_log;

        Client * AddClient(Socket *clientSocket);
        void RemoveClient(Client *clientToRemove);

        void Log(string msg);
        void SendToChannel(string msg, Channel *channel);
        void SendToChannel(string msg, Channel *channel, Client *sender);
        void SendToClient(string msg, Client *receiver);
        void SendToClient(string msg, Client *receiver, Client *sender);

        void ExecuteCommand(string commandReceived, Client *sender);
        void CommandHelp(Client *sender);
        void CommandPing(Client *sender);
        void CommandJoin(string channelName, Client *sender);
        void CommandPart(Client *sender);
        void CommandNickname(string nickname, Client *sender);
        void CommandKick(string nickname, Client *sender);
        void CommandWhois(string nickname, Client *sender);
        void CommandMute(string nickname, Client *sender);
        void CommandUnmute(string nickname, Client *sender);
        void CommandMode(bool isPrivate, Client *sender);
        void CommandInvite(string nickname, Client *sender);
        void CommandInvalid(Client *sender);

        bool RespondIfClientNotAdm(Client *client);
        bool RespondIfNickNonExisting(string nickname, Client *client);
        bool RespondIfNotEnoughArguments(int have, int needed,  Client *client);
        bool RespondIfNotInChannel(Client *client);

        Channel * CreateChannel(string channelName);
        void DeleteChannel(Channel *channel);
        Channel * GetChannelWithName(string channelName);

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