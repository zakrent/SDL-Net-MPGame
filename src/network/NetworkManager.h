//
// Created by zakrent on 9/28/17.
//

#ifndef GAME_MP_SERVER_NETWORK_H
#define GAME_MP_SERVER_NETWORK_H

#include <SDL_net.h>
#include <vector>
#include "Client.h"
#include "../misc/log.h"

namespace network {
    class NetworkManager {
    private:
        TCPsocket serverTcpsock;
        SDLNet_SocketSet socketSet;

        std::vector<Client> clients;

    public:

        NetworkManager();
    };
}


#endif //GAME_MP_SERVER_NETWORK_H
