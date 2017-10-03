//
// Created by zakrent on 9/26/17.
//

#ifndef GAME_MP_SERVER_PROGRAM_H
#define GAME_MP_SERVER_PROGRAM_H

#include <vector>
#include "entity/BaseEntity.h"
#include <SDL2/SDL.h>
#include <SDL_net.h>
#include <iostream>
#include "misc/log.h"
#include "network/NetworkManager.h"

class Program {
private:
    const int MIN_UPDATE_TIME = 10;
    int lastUpdate;
    network::NetworkManager networkManager;
    std::vector<entity::BaseEntity*> entities;
public:
    void startMainLoop();

    Program();
    ~Program();

};


#endif //GAME_MP_SERVER_PROGRAM_H
