#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <string>
#include <thread>
#include "util.h"
#include "mkSocket.h"

#define MAX_CHARS_IN_MESSAGE 4096
#define CONNECT_ATTEMPT_TIMEOUT 10

using namespace std;

class Application {

    private:
        Socket * socket;

        bool CheckConnectCommand(string command, string *ip, int *port);

    protected:
        void ReceiveMessages();

    public:
        Application();

        void ConnectionStage();
        void Launch();

        ~Application();
};

#endif