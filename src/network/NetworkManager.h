//
// Created by zakrent on 9/28/17.
//

#ifndef GAME_MP_SERVER_NETWORK_H
#define GAME_MP_SERVER_NETWORK_H

#include <SDL_net.h>
#include <vector>
#include "NetworkClient.h"
#include <SDL_net.h>
#include "../misc/log.h"

namespace network {
    class NetworkManager {
    private:
        TCPsocket serverTcpsock;
        SDLNet_SocketSet socketSet;

        std::vector<NetworkClient> clients;

        GameState currentGameState;

        void addClient(NetworkClient client);
    public:

        void generateCurrentGameState(std::vector<entity::BaseEntity*> entities);
        void updateClientState();
        void checkForIncomingTraffic();
        explicit NetworkManager(Uint16 port);
    };
}


#endif //GAME_MP_SERVER_NETWORK_H
