//
// Created by zakrent on 9/26/17.
//

#include <SDL2/SDL.h>
#include <SDL_net.h>
#include <iostream>
#include "Program.h"

Program::Program() {
    int error = SDL_Init(SDL_INIT_EVERYTHING);
    if(error < 0){
        std::cerr<<"Error initializing SDL "<<SDL_GetError();
        std::abort();
    }
    error = SDLNet_Init();
    if(error < 0){
        std::cerr<<"Error initializing SDLnet "<<SDL_GetError();
        std::abort();
    }
    lastUpdate=SDL_GetTicks();
}

Program::~Program() {
    SDLNet_Quit();
    SDL_Quit();
}

void Program::startMainLoop() {
    bool running = true;
    while(running){

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

