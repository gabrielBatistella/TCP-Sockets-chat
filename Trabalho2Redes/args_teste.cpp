#include <iostream>
#include <string>

using namespace std;

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

        if(currentPos == (int) string::npos || currentPos == original.size()-1) {
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

int main(void) {
    string original("/connect  arg1   ,  arg2  arg3  -p  ");
    string command;
    int argc;
    char **argv;
    getCommandAndArgs(original, &command, &argc, &argv);

    cout << "Comando: "<< command << endl;
    cout << "Argumentos: "<< argc << endl;

    for(int i = 0; i < argc; i++) {
        cout << i << " : " << argv[i] << endl;
    }


    freeArgvMemory(argc, &argv);

    return 0;
}