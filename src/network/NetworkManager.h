//
// Created by zakrent on 9/28/17.
//

#ifndef GAME_MP_SERVER_NETWORK_H
#define GAME_MP_SERVER_NETWORK_H

#include <SDL_net.h>
#include <vector>
#include "Client.h"
#include <SDL_net.h>
#include "../misc/log.h"

namespace network {
    class NetworkManager {
    private:
        TCPsocket serverTcpsock;
        SDLNet_SocketSet socketSet;

        std::vector<Client> clients;

        GameState currentGameState;

        void addClient(Client client);
    public:

        void generateCurrentGameState(std::vector<entity::BaseEntity*> entities);
        void updateClientState();
        void checkForIncomingTraffic();
        NetworkManager();
    };
}


#endif //GAME_MP_SERVER_NETWORK_H
