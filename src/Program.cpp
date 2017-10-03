//
// Created by zakrent on 9/26/17.
//

#include "Program.h"

Program::Program() {
    int error = SDL_Init(SDL_INIT_EVERYTHING);
    consoleLog::logMessage(consoleLog::logLevel::info, "Server startup...");
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

    entities.push_back(new entity::BaseEntity(math::Vector2(0,0), math::Vector2(10,0)));
}

Program::~Program() {
    consoleLog::logMessage(consoleLog::logLevel::info, "Server shutting down...");

    for(int i = 0; i < entities.size(); i++) {
        delete entities[i];
    }

    SDLNet_Quit();
    SDL_Quit();
}

void Program::startMainLoop() {
    bool running = true;
    while(running){

        networkManager.checkForIncomingTraffic();

        for(int i = 0; i < entities.size(); i++){
            entities[i]->update();
            if(entities[i]->shouldBeDestroyed){
                delete entities[i];
                entities.erase(entities.begin()+i);
            }
        }

        networkManager.generateCurrentGameState(entities);
        networkManager.updateClientState();

        SDL_Event event;
        while( SDL_PollEvent( &event) != 0 ) {
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

