//
// Created by zakrent on 11/10/17.
//

#ifndef GAME_MP_SERVER_CLIENT_H
#define GAME_MP_SERVER_CLIENT_H


#include <SDL_net.h>

class Client {
    TCPsocket tcpsock;
    SDLNet_SocketSet socketSet;

public:
    void update();

    Client(char *host, Uint16 port);
    ~Client();
};

#endif //GAME_MP_SERVER_CLIENT_H
