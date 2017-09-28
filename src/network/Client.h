//
// Created by zakrent on 9/28/17.
//

#ifndef GAME_MP_SERVER_CLIENT_H
#define GAME_MP_SERVER_CLIENT_H

#include <SDL_net.h>
#include "../misc/types.h"

namespace network {
    struct Client {
        TCPsocket socket;
        uint32 timeout;

        Client(TCPsocket _socket, uint32_t _timeout) : socket(_socket), timeout(_timeout) {}
    };
}

#endif //GAME_MP_SERVER_CLIENT_H
