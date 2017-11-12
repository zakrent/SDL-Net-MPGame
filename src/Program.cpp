//
// Created by zakrent on 9/26/17.
//

#include "Program.h"

Program::Program() {
    int error = SDL_Init(SDL_INIT_EVERYTHING);
    consoleLog::logMessage(consoleLog::logLevel::info, "SDL init...");
    if(error < 0){
        consoleLog::logMessage(consoleLog::logLevel::error, "Error initializing SDL!");
        std::abort();
    }
    error = SDLNet_Init();
    if(error < 0){
        consoleLog::logMessage(consoleLog::logLevel::error, "Error initializing SDLnet!");
        std::abort();
    }
    lastUpdate=SDL_GetTicks();
    server = nullptr;
    client = nullptr;
}

Program::~Program() {
    delete server;
    delete client;
    SDLNet_Quit();
    SDL_Quit();
}

void Program::startMainLoop(bool startServer, bool startClient, char *host, Uint16 port) {
    bool running = true;

    if(startServer){
        server = new Server(port);
    }
    if(startClient){
        client = new Client(host, port);
    }

    while(running){
        if(startServer){
            server->update();
        }
        if(startClient){
            client->update();
        }

        SDL_Event event{};
        while(SDL_PollEvent(&event) != 0 ) {
            switch(event.type){
                case SDL_QUIT:
                    running = false;
                    break;
                default:
                    break;
            }
        }

        if (SDL_GetTicks() < lastUpdate + MIN_UPDATE_TIME) {
            SDL_Delay((lastUpdate + MIN_UPDATE_TIME) - SDL_GetTicks());
        }
        lastUpdate = SDL_GetTicks();
    }
}

