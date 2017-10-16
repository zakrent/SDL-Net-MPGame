//
// Created by zakrent on 9/28/17.
//

#ifndef GAME_MP_SERVER_CLIENT_H
#define GAME_MP_SERVER_CLIENT_H

#include <SDL_net.h>
#include "../misc/types.h"
#include "states/GameState.h"
#include "states/EventState.h"

namespace network {
    struct Client {
        TCPsocket socket;
        uint32 timeout;
        GameState clientGameState;

        std::vector<EventState> events;

        Client(TCPsocket _socket, uint32_t _timeout)
                : socket(_socket), timeout(_timeout), clientGameState() {}
    };
}

#endif //GAME_MP_SERVER_CLIENT_H
