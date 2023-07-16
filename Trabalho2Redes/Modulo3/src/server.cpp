#include "../headers/server.h"

Client * Server::AddClient(Socket *clientSocket) {
    m_cli.lock();
    if(this->amountClients >= this->maxClients) {
        m_cli.unlock();
        return NULL;
    }
    
    Client *client = new Client(clientSocket);  // Já cria com Channel = NULL, mute = false, adm = false e nickname = ""

    this->amountClients += 1;
    this->clientsConnected[NULL]->push_back(client);
    m_cli.unlock();
    
    thread clientHandling([] (Server *server, Client *client) {server->HandleClient(client);}, this, client);
    clientHandling.detach();
    
    return client;
}

void Server::RemoveClient(Client *clientToRemove) {
    m_cli.lock();
    vector<Client *> *clientsList = this->clientsConnected[clientToRemove->GetChannel()];
    
    for(vector<Client *>::iterator cli = clientsList->begin() ; cli != clientsList->end() ; cli++) {
        if((*cli) == clientToRemove) {
            delete (*cli);
            clientsList->erase(cli);
            this->amountClients -= 1;
            break;
        }
    }
    m_cli.unlock();
}

void Server::Log(string msg) {
    m_log.lock();
    cout << "-> " << msg << endl;
    m_log.unlock();
}

void Server::SendToChannel(string msg, Channel *channel) {
    Log("(server)" + channel->GetName() + " " + msg);
    string msgToSend = msg + " <<<<<";

    vector<Client *> *clientsInChannel = this->clientsConnected[channel];
    if(clientsInChannel == NULL) return;

    for(vector<Client *>::iterator cli = clientsInChannel->begin() ; cli != clientsInChannel->end() ; cli++) {
        SendToClient(msgToSend, (*cli));
    }
}
        
void Server::SendToChannel(string msg, Channel *channel, Client *sender) {
    Log("(" + sender->GetNickname() + ")" + channel->GetName() + " " + msg);
    string msgToSend = msg;

    vector<Client *> *clientsInChannel = clientsConnected[channel];
    if(clientsInChannel == NULL) return;

    for(vector<Client *>::iterator cli = clientsInChannel->begin() ; cli != clientsInChannel->end() ; cli++) {
        SendToClient(msgToSend, (*cli), sender);
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

    if(command == "/help") {
        CommandHelp(sender);
    }
    else if(command == "/ping") {
        CommandPing(sender);
    }
    else if(command == "/join"){
        if(RespondIfNotEnoughArguments(argc, 1)) {
            CommandJoin(string(argv[0]), sender);
        }
    }
    else if(command == "/part"){
        CommandPart(sender);
    }
    else if(command == "/nickname"){
        if(RespondIfNotEnoughArguments(argc, 1)) {
            CommandNickname(string(argv[0]), sender);
        }
    }
    else if(command == "/kick"){
        if(RespondIfNotEnoughArguments(argc, 1)) {
            CommandKick(string(argv[0]), sender);
        }
    }
    else if(command == "/whois"){
        if(RespondIfNotEnoughArguments(argc, 1)) {
            CommandWhois(string(argv[0]), sender);
        }
    }
    else if(command == "/mute"){
        if(RespondIfNotEnoughArguments(argc, 1)) {
            CommandMute(string(argv[0]), sender);
        }
    }
    else if(command == "/unmute"){
        if(RespondIfNotEnoughArguments(argc, 1)) {
            CommandUnmute(string(argv[0]), sender);
        }
    }
    else if(command == "/mode"){
        if(RespondIfNotEnoughArguments(argc, 1)) {
            string argument = string(argv[0]);
            bool convertedArgument = NULL;
            if(argument == "public") convertedArgument = false;
            else if(argument == "private") convertedArgument = true;          
            CommandMode(convertedArgument, sender);
        }
    }
    else if(command == "/invite"){
        if(RespondIfNotEnoughArguments(argc, 1)) {
            CommandInvite(string(argv[0]), sender);
        }
    }
    else {
        CommandInvalid(sender);
    }

    freeArgvMemory(argc, &argv);
}

void Server::CommandHelp(Client *sender) {
    string commands = "Os comandos do servidor são:\n";
    commands += "/connect IP PORT - Conecta ao servidor pelo IP e PORT fornecidos, ligando a aplicação\n";
    commands += "/quit - Sai do servidor, desligando a aplicação\n";
    commands += "/help - Obter informações sobre os comandos\n";
    commands += "/ping - Recebe uma resposta 'pong' do servidor\n";
    commands += "/join CHANNEL_NAME - Entra no canal desejado\n";
    commands += "/part - Deixa o canal atual\n";
    commands += "/nickname NICKNAME - Define/troca seu apelido\n";
    commands += "/kick NICKNAME - Expulsa usuário do canal (apenas adm)\n";
    commands += "/whois NICKNAME - Descobre o IP do usuário (apenas adm)\n";
    commands += "/mute NICKNAME - Muta usuário do canal (apenas adm)\n";
    commands += "/unmute NICKNAME - Desmuta usuário do canal (apenas adm)\n";
    commands += "/mode 'public'|'private' - Determina se o canal é público ou privado (apenas adm)\n";
    commands += "/invite NICKNAME - Convida usuário ao canal, permitindo sua entrada se este for privado (apenas adm)\n\n";
    
    SendToClient(commands, sender);
}

void Server::CommandPing(Client *sender) {
    if(sender->GetNickname() == "") {
        Log("um cliente enviou um ping");
    }
    else {
        Log(sender->GetNickname() + " enviou um ping");
    }
    SendToClient("pong", sender);
    Log("servidor respondeu com um pong");
}

void Server::CommandJoin(string channelName, Client *sender) {
    if(sender->GetChannel() != NULL) {
        SendToClient("Você já está em um canal", sender);
        return;
    }

    if(sender->GetNickname() == "") {
        SendToClient("Você deve setar um nickname primeiro", sender);
        return;
    }
    
    Channel *channel = this->GetChannelWithName(channelName);  
    if(channel == NULL) {        
        try {
            channel = CreateChannel(channelName);
            clientsConnected[channel]->push_back(sender);
            sender->SetChannel(channel);
            sender->SetAdm(true);
            sender->SetMute(false);
            Log(sender->GetNickname() + " abriu o canal " + channelName);
            SendToChannel(sender->GetNickname() + " ingressou no canal", channel);
        }
        catch(...) {
            delete channel;
            SendToClient("O canal não foi aberto porque o nome escolhido é inválido", sender);
        }
    }
    else if((channel->IsPrivate() && channel->IsClientInvited(sender->GetNickname())) || !(channel->IsPrivate())){
        clientsConnected[channel]->push_back(sender);
        sender->SetChannel(channel);
        sender->SetAdm(false);
        sender->SetMute(false);
        SendToChannel(sender->GetNickname() + " ingressou no canal", channel);  
    } else {
        SendToClient("O canal em que você tentou ingressar é privado", sender);
    }
}

void Server::CommandPart(Client *sender) {
    if(RespondIfNotInChannel(sender)) return;

    vector<Client *> *clientList = this->clientsConnected[sender->GetChannel()];
    for(vector<Client *>::iterator cli = clientList->begin() ; cli != clientList->end() ; cli++) {
        if((*cli) == sender) {
            clientList->erase(cli);
            break;
        }
    }
    this->clientsConnected[NULL]->push_back(sender);
    sender->SetChannel(NULL);

    
}

void Server::CommandNickname(string nickname, Client *sender) {
    
}

void Server::CommandKick(string nickname, Client *sender){
    if(RespondIfNotInChannel(sender)) return;
    if(RespondIfClientNotAdm(sender)) return;
    if(RespondIfNickNonExisting(nickname, sender)) return;

    vector<Client *> *clientList = this->clientsConnected[sender->GetChannel()];
    for(vector<Client *>::iterator cli = clientList->begin() ; cli != clientList->end() ; cli++) {
        if((*cli)->GetNickname() == nickname) {
            SendToChannel("O usuário " + nickname + " foi expulso do canal pelo admin " + sender->GetNickname(), sender->GetChannel());
            RemoveClient((*cli));
            return;
        }
    }
}

void Server::CommandWhois(string nickname, Client *sender){
    if(RespondIfNotInChannel(sender)) return;
    if(RespondIfClientNotAdm(sender)) return;
    if(RespondIfNickNonExisting(nickname, sender)) return;

    vector<Client *> *clientList = this->clientsConnected[sender->GetChannel()];
    for(vector<Client *>::iterator cli = clientList->begin() ; cli != clientList->end() ; cli++) {
        if((*cli)->GetNickname() == nickname) {
            SendToClient("O IP encontrado para o nickname " + nickname + " é: " + (*cli)->GetSocket()->GetIP(), sender);
            return;
        }
    }
}

void Server::CommandMute(string nickname, Client *sender){
    if(RespondIfNotInChannel(sender)) return;
    if(RespondIfClientNotAdm(sender)) return;
    if(RespondIfNickNonExisting(nickname, sender)) return;
    
    vector<Client *> *clientList = this->clientsConnected[sender->GetChannel()];
    for(vector<Client *>::iterator cli = clientList->begin() ; cli != clientList->end() ; cli++) {
        if((*cli)->GetNickname() == nickname) {
            (*cli)->SetMute(true);
            return;
        }
    }
}

void Server::CommandUnmute(string nickname, Client *sender){
    if(RespondIfNotInChannel(sender)) return;
    if(RespondIfClientNotAdm(sender)) return;
    if(RespondIfNickNonExisting(nickname, sender)) return;
    
    vector<Client *> *clientList = this->clientsConnected[sender->GetChannel()];
    for(vector<Client *>::iterator cli = clientList->begin() ; cli != clientList->end() ; cli++) {
        if((*cli)->GetNickname() == nickname) {
            (*cli)->SetMute(false);
            return;
        }
    }
}

void Server::CommandMode(bool isPrivate, Client *sender) {
    if(RespondIfNotInChannel(sender)) return;
    if(RespondIfClientNotAdm(sender)) return;

    if(isPrivate == NULL) {
        SendToClient("Valor inválido para mode", sender);
        return;
    }
    
    sender->GetChannel()->SetPrivate(isPrivate);
}

void Server::CommandInvite(string nickname, Client *sender){
    if(RespondIfNotInChannel(sender)) return;
    if(RespondIfClientNotAdm(sender)) return;
    
    sender->GetChannel()->InviteClient(nickname);
}

void Server::CommandInvalid(Client *sender) {
    SendToClient("Comando inválido!", sender);
}

bool Server::RespondIfClientNotAdm(Client *client) {
    if(!client->IsAdm()) {
        SendToClient("Você precisa ser admin para utilizar esse comando", client);
        return true;
    }
    else {
        return false;
    }
}

bool Server::RespondIfNickNonExisting(string nickname, Client *client) {
    vector<Client *> *clientList = this->clientsConnected[client->GetChannel()];
    for(vector<Client *>::iterator cli = clientList->begin() ; cli != clientList->end() ; cli++) {
        if((*cli)->GetNickname() == nickname) {
            return false;
        }
    }
    SendToClient("O nickname passado não foi encontrado no canal", client);
    return true;
}

bool Server::RespondIfNotEnoughArguments(int have, int needed, Client *client) {
    if(have < needed) {
        SendToClient("Argumentos insuficientes para o comando", client);
        return true;
    }
    else {
        return false;
    }
}

bool Server::RespondIfNotInChannel(Client *client) {
    if(client->GetChannel() == NULL) {
        SendToClient("Você deve entrar em um canal primeiro", client);
        return true;
    }
    else {
        return false;
    }
}

Channel *Server::CreateChannel(string channelName) {
    if(GetChannelWithName(channelName) != NULL) return NULL;
    Channel *channel = new Channel(channelName);
    clientsConnected[channel] = new vector<Client *>();
    return channel;
}

void Server::DeleteChannel(Channel *channel) {
    vector<Client *> *clientsList = (this->clientsConnected)[channel];
    for(vector<Client *>::iterator cli = clientsList->begin() ; cli != clientsList->end() ; cli++) {
        delete (*cli);
    }
    clientsList->clear();
    delete clientsList;
    delete channel;
    clientsConnected.erase(channel);
}

Channel * GetChannelWithName(string channelName) {
    for(map<Channel *, vector<Client *> *>::iterator cli = this->clientsConnected.begin() ; cli != this->clientsConnected.end() ; cli++) {
        Channel *channel = (*cli).first;
        if(channel->GetName() == channelName) {
            return channel;
        }
    }
    return NULL;
}

void Server::ListenForClients() {
    while(true) {
        Socket *socket = this->listenerSocket->Accept();
        Client *newClient = AddClient(socket);
        if(newClient == NULL) {
            delete socket;
        }
        else {
            Log("Um novo cliente entrou no servidor");
        }
    }
}

void Server::HandleClient(Client *client) {
    while(true) {
        string receiveMsg = client->GetSocket()->Receive();
        if(receiveMsg == "") {
            if(client->GetChannel() != NULL) {
                SendToChannel(client->GetNickname() + " saiu do servidor", client->GetChannel());
            }
            RemoveClient(client);
            return;
        }
        else if(receiveMsg.at(0) == '/') {
            ExecuteCommand(receiveMsg, client);
        }
        else if(client->GetChannel() != NULL) {
            if(client->IsMute()) {
                SendToClient("Você está mutado. Suas mensagens não são lidas pelos outros participantes do canal.", client);
            }
            else {
                SendToChannel(receiveMsg, client->GetChannel(), client);
            }
        }
    }
}

Server::Server(string ip, int port, int maxClients) {
    this->listenerSocket = new Socket(ip, port);
    this->maxClients = maxClients;
    clientsConnected[NULL] = new vector<Client *>();
}

Server::Server(string ip, int maxClients) {
    this->listenerSocket = new Socket(ip);
    this->maxClients = maxClients;
    clientsConnected[NULL] = new vector<Client *>();
}

Server::Server(int port, int maxClients) {
    this->listenerSocket = new Socket(port);
    this->maxClients = maxClients;
    clientsConnected[NULL] = new vector<Client *>();
}

Server::Server(int maxClients) {
    this->listenerSocket = new Socket();
    this->maxClients = maxClients;
    clientsConnected[NULL] = new vector<Client *>();
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
    for(map<Channel *, vector<Client *> *>::iterator pair = this->clientsConnected.begin() ; pair != this->clientsConnected.end() ; pair++) {
        Channel *channel = (*pair).first;
        vector<Client *> *clientsList = (*pair).second;

        for(vector<Client *>::iterator cli = clientsList->begin() ; cli != clientsList->end() ; cli++) {
            delete (*cli);
        }
        clientsList->clear();

        delete channel;
        delete clientsList;
    }
    this->clientsConnected.clear();
    m_cli.unlock();
}
