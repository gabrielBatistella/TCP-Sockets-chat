#include <locale.h>
#include <signal.h>
#include "../headers/server.h"

#define MAX_CONNECTIONS 50
#define PORT_DEFAULT 3000 

using namespace std;


bool leave = false;

void catchInterruption(int a);


int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    signal(SIGINT, catchInterruption);
    
    Server *server = new Server(MAX_CONNECTIONS);
    server->Start();

    while(!leave) {};
    delete server;

    return EXIT_SUCCESS;
}

void catchInterruption(int a) {
    leave = true;
}