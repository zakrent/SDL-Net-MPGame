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
#include "math/physics.h"
#include "Server.h"
#include "Client.h"

class Program {
private:
    const int MIN_UPDATE_TIME = 60;
    int lastUpdate;

    Server* server;
    Client* client;

public:
    void startMainLoop(bool startServer, bool startClient, char *host, Uint16 port);
    Program();
    ~Program();

};


#endif //GAME_MP_SERVER_PROGRAM_H
