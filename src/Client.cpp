//
// Created by zakrent on 11/10/17.
//

#include <iostream>
#include "Client.h"
#include "network/states/EventState.h"

Client::Client(char *host, Uint16 port) {
    IPaddress ipaddress;
    SDLNet_ResolveHost(&ipaddress, host, port);
    tcpsock=SDLNet_TCP_Open(&ipaddress);
    socketSet=SDLNet_AllocSocketSet(1);
    SDLNet_TCP_AddSocket(socketSet,tcpsock);
}

Client::~Client() {

}

void Client::update() {
    network::EventState event(14);
    char buffer[20];
    int length = event.serialize(buffer);
    SDLNet_TCP_Send(tcpsock, buffer, length);
    SDLNet_CheckSockets(socketSet, 0);
    while(SDLNet_SocketReady(tcpsock)) {
        strncpy(buffer, "", 20);
        SDLNet_TCP_Recv(tcpsock, buffer, 4);
        std::cout << "ID: " << network::unserializeUInt32(buffer) << std::endl;
        SDLNet_TCP_Recv(tcpsock, buffer, 2);
        uint16 delta = network::unserializeUInt16(buffer);
        std::cout << "DT: " << delta << std::endl;
        if ((delta & 0b0000000000000001) == 0b0000000000000001) {
            std::cout << "Pos" << std::endl;
            SDLNet_TCP_Recv(tcpsock, buffer, 8);
            std::cout << network::unserializeVector(buffer).x << std::endl;
            std::cout << network::unserializeVector(buffer).y << std::endl;
        }
        if ((delta & 0b0000000000000010) == 0b0000000000000010) {
            std::cout << "Vel" << std::endl;
            SDLNet_TCP_Recv(tcpsock, buffer, 8);
            std::cout << network::unserializeVector(buffer).x << std::endl;
            std::cout << network::unserializeVector(buffer).y << std::endl;
        }
        if ((delta & 0b0000000000000100) == 0b0000000000000100) {
            std::cout << "Src" << std::endl;
            SDLNet_TCP_Recv(tcpsock, buffer, 4);
            std::cout << network::unserializeUInt32(buffer) << std::endl;
            SDLNet_TCP_Recv(tcpsock, buffer, 4);
            std::cout << network::unserializeUInt32(buffer) << std::endl;
            SDLNet_TCP_Recv(tcpsock, buffer, 4);
            std::cout << network::unserializeUInt32(buffer) << std::endl;
            SDLNet_TCP_Recv(tcpsock, buffer, 4);
            std::cout << network::unserializeUInt32(buffer) << std::endl;
        }
    }
}
