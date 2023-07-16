#include "../headers/util.h"

void checkOperation(int result, string errorMsg) {
    if(result < 0) {
        cerr << errorMsg << endl;
        exit(EXIT_FAILURE);
    }
}

void getCommandAndArgs(string original, string *command, int *argc, char ***argv) {
    *argc = 0;
    *argv = NULL;
    
    int indexFirstSpace = original.find(' ');
    if(indexFirstSpace == (int) string::npos) {
        *command = original;
        return;
    } 

    *command = original.substr(0, indexFirstSpace);

    int previousPos = indexFirstSpace;
    int currentPos = indexFirstSpace;

    bool posIsInFinalOfString = false;
    while(!posIsInFinalOfString) { 
        currentPos = original.find(' ', previousPos + 1);
        if(currentPos == previousPos+1) {
            //Espaço seguido de espaço
            //do nothing
        } else {
            (*argc) += 1;
            string arg = original.substr(previousPos+1, currentPos - (previousPos+1));
            
            *argv = (char **) realloc(*argv, (*argc) * sizeof(char *));
            (*argv)[(*argc)-1] = (char *) calloc(arg.size()+1, sizeof(char)); 
            arg.copy((*argv)[(*argc)-1], arg.size()+1, 0);
        }

        if(currentPos == (int) string::npos || currentPos == ((int)original.size())-1) {
            // connect ... argN
            posIsInFinalOfString = true;
        } 
        
        previousPos = currentPos;
    }
}

void freeArgvMemory(int argc, char ***argv) {
    if(*argv != NULL) {
        for(int i = 0; i < argc; i++) {
            free((*argv)[i]);
        }
        free(*argv);
        *argv = NULL;
    }
}

void setIPandPortFromArgs(int argc, char **argv, string *ip, int *port) {
    switch(argc) {
        case 0:
            //*ip = IP_DEFAULT;
            //*port = PORT_DEFAULT;
            break;
        case 1:
            *ip = argv[0];
            //*port = PORT_DEFAULT;
            break;
        case 2:
            *ip = argv[0];
            *port = stoi(argv[1]);
            break;
        default:
            throw invalid_argument("Quantidade incompatível de argumentos");
    }
    if(!ipCheck(*ip)) {
        throw invalid_argument("IP inválido");
    }
    if(!portCheck(*port)) {
        throw invalid_argument("Porta inválida");
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