#ifndef UTIL_H
#define UTIL_H 

#include <iostream>
#include <string>

using namespace std;

void checkOperation(int result, string errorMsg);

void getCommandAndArgs(string original, string *command, int *argc, char ***argv);
void freeArgvMemory(int argc, char ***argv);

void setIPandPortFromArgs(int argc, char **argv, string *ip, int *port);
bool ipCheck(string ip);
bool portCheck (int port);

#endif