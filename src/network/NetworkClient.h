//
// Created by zakrent on 9/28/17.
//

#ifndef GAME_MP_SERVER_NETWORKCLIENT_H
#define GAME_MP_SERVER_NETWORKCLIENT_H

#include <SDL_net.h>
#include "../misc/types.h"
#include "states/GameState.h"
#include "states/EventState.h"
#include "../math/random.h"

namespace network {
    struct NetworkClient {
        uint32 playerEntityID;
        TCPsocket socket;
        uint32 timeout;
        GameState clientGameState;

        std::vector<EventState> events;

        NetworkClient(TCPsocket _socket, uint32_t _timeout)
                : socket(_socket), timeout(_timeout), clientGameState(), playerEntityID(math::getRandomId()) {}
    };
}

#endif //GAME_MP_SERVER_CLIENT_H
