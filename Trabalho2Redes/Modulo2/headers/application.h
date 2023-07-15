#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <string>
#include <thread>
#include "util.h"
#include "mkSocket.h"

using namespace std;

class Application {

    private:
        Socket * socket;
        bool isConnected;

    protected:
        void ReceiveMessages();

    public:
        Application();

        void ConnectionStage();
        void Launch();

        ~Application();
};

#endif