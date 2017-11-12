//
// Created by zakrent on 11/10/17.
//

#ifndef GAME_MP_SERVER_CLIENT_H
#define GAME_MP_SERVER_CLIENT_H


#include <SDL_net.h>
#include <vector>
#include "visual/Renderer.h"
#include "network/states/EntityState.h"

class Client {
    TCPsocket tcpsock;
    SDLNet_SocketSet socketSet;
    visual::Renderer renderer;
    std::vector<network::EntityState> states;

    network::EntityState* getStateWithId(uint64 id);

public:
    void update();

    Client(char *host, Uint16 port);
    ~Client();
};

#endif //GAME_MP_SERVER_CLIENT_H
