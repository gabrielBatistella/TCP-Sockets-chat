#include <iostream>
#include <locale.h>
#include <signal.h>
#include "../headers/util.h"
#include "../headers/mkSocket.h"

#define MAX_CHARS_IN_MESSAGE 4096
#define IP_DEFAULT "127.0.0.1"
#define PORT_DEFAULT 3000

using namespace std;


void waitForConnectionCommand();


int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    signal(SIGINT, SIG_IGN);
    
    string targetIP = IP_DEFAULT;
    int targetPort = PORT_DEFAULT;
    setIPandPortFromArgs(argc, argv, &targetIP, &targetPort);

    waitForConnectionCommand();

    Socket *socket = new Socket();
    bool connected = socket->Connect(targetIP, targetPort, 5);
    if(connect) {

    }

    delete socket;

    return EXIT_SUCCESS;
}

void waitForConnectionCommand() {
    string command;
    while(true) {
        cout << "Digite o comando /connect para entrar no chat!" << endl;
        cin >> command;
        if(command == "/connect") break;
        if(command == "/quit") exit(EXIT_SUCCESS);
        cout << endl;
    }
}