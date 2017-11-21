//
// Created by zakrent on 11/10/17.
//

#include <iostream>
#include "Client.h"
#include "network/states/EventState.h"
#include "network/states/events/HeartBeatEvent.h"
#include "network/states/events/ControlEvent.h"

Client::Client(char *host, Uint16 port) {
    IPaddress ipaddress{};
    SDLNet_ResolveHost(&ipaddress, host, port);
    tcpsock=SDLNet_TCP_Open(&ipaddress);
    socketSet=SDLNet_AllocSocketSet(1);
    SDLNet_TCP_AddSocket(socketSet,tcpsock);
}

Client::~Client() = default;

network::EntityState* Client::getStateWithId(uint64 id){
    for (int i = 0; i < states.size(); i++) {
        if(states[i].getId() == id){
            return &states[i];
        }
    }
    return nullptr;
}

void Client::update() {
    char buffer[50];
    strncpy(buffer, "", 50);
    network::HeartBeatEvent heartBeatEvent;
    int length = heartBeatEvent.serialize(buffer);
    SDLNet_TCP_Send(tcpsock, buffer, length);

    network::ControlEvent controlEvent;
    length = controlEvent.serialize(buffer);
    SDLNet_TCP_Send(tcpsock, buffer, length);

    while(SDLNet_CheckSockets(socketSet, 0)) {
        strncpy(buffer, "", 20);
        SDLNet_TCP_Recv(tcpsock, buffer, 4);
        uint32 id = network::unserializeUInt32(buffer);
        network::EntityState* state = getStateWithId(id);
        if(state){
            state->networkUpdate(tcpsock);
        }
        else{
            states.emplace_back(id, math::Vector2(0,0), math::Vector2(0,0), SDL_Rect{0,0,0,0});
            network::EntityState* newState = &states.back();
            newState->networkUpdate(tcpsock);
        }
    }
    renderer.renderStates(&states);
}
