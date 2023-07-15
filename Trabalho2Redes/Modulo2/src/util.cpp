#include "../headers/util.h"

void checkOperation(int result, string errorMsg) {
    if(result < 0) {
        cerr << errorMsg << endl;
        exit(EXIT_FAILURE);
    }
}

void setIPandPortFromArgs(int argc, char **argv, string *ip, int *port) {
    switch(argc) {
        case 1:
            //*ip = IP_DEFAULT;
            //*port = PORT_DEFAULT;
            break;
        case 2:
            *ip = argv[1];
            //*port = PORT_DEFAULT;
            break;
        case 3:
            *ip = argv[1];
            *port = stoi(argv[2]);
            break;
        default:
            cerr << "Erro no input!" << endl;
            exit(EXIT_FAILURE);
    }
    if(!ipCheck(*ip)) {
        cerr << "IP inválido" << endl;
        exit(EXIT_FAILURE);
    }
    if(!portCheck(*port)) {
        cerr << "Porta inválida" << endl;
        exit(EXIT_FAILURE);
    }
}

bool ipCheck(string ip) {
    int count = 0;
    int previousPos = -1;
    int currentPos = 0;
    while(count < 4) {
        currentPos = ip.find('.', previousPos + 1);
        if(currentPos == (int) string::npos && count != 3) return false;
        string token = ip.substr(previousPos + 1, currentPos - previousPos - 1);
        try {
            int number = stoi(token);
            if(number < 0 || number > 255) return false;
        }
        catch(...) {
            return false;
        }
        previousPos = currentPos;
        count++;
    }

    if(count != 4) return false;

    return true;
}

bool portCheck(int port) {
    return (port >= 0 && port <= 65535);
}