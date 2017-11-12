#include <iostream>
#include "Program.h"

int main(int argc, char* argv[]) {

    bool startServer = false;
    bool startClient = false;

    for (int i = 1; i < argc; ++i) {
        if(strcmp(argv[i], "--server") == 0){
            startServer = true;
        }
        if(strcmp(argv[i], "--client") == 0){
            startClient = true;
        }
    }

    Program program;
    program.startMainLoop(startServer, startClient, (char*)"127.0.0.1", 2000);
    return 0;
}