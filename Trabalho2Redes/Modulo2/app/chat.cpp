#include <iostream>
#include <locale.h>
#include <signal.h>
#include "../headers/application.h"

using namespace std;


int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    signal(SIGINT, SIG_IGN);

    Application *app = new Application();
    app->ConnectionStage();
    app->Launch();

    return EXIT_SUCCESS;
}