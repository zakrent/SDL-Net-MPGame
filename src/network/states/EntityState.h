//
// Created by zakrent on 10/1/17.
//

#ifndef GAME_MP_SERVER_ENTITYSTATE_H
#define GAME_MP_SERVER_ENTITYSTATE_H

#include <SDL_video.h>
#include <iostream>
#include <SDL_net.h>
#include "../../misc/types.h"
#include "../../math/Vector2.h"
#include "../serialize.h"

namespace network{
    class EntityState{
        uint32 id{};
        math::Vector2 position;
        math::Vector2 velocity;
        SDL_Rect srcrect;

    public:
        uint32 getId(){
            return id;
        }

        uint16 getDelta(EntityState prevState){
            bool posChanged = !(position == prevState.position);
            bool velChanged = !(velocity == prevState.velocity);
            bool sctChanged = (srcrect.w != prevState.srcrect.w && srcrect.h != prevState.srcrect.h
                               && srcrect.x != prevState.srcrect.x && srcrect.y != prevState.srcrect.y);
            uint16 delta = 0;
            delta += posChanged ? 1 : 0;
            delta += velChanged ? 2 : 0;
            delta += sctChanged ? 4 : 0;

            return delta;
        }

        SDL_Rect getSrcrect(){
            return srcrect;
        }

        math::Vector2 getPosition(){
            return position;
        }

        int serialize(char* buffer, uint16 delta){
            int offset = 0;
            serializeUInt32(buffer+offset, id);
            offset += 4;
            serializeUInt16(buffer+offset, delta);
            offset += 2;
            if((delta & 0b0000000000000001) == 0b0000000000000001){
                serializeVector(buffer+offset,position);
                offset += 8;
            }
            if((delta & 0b0000000000000010) == 0b0000000000000010){
                serializeVector(buffer+offset,velocity);
                offset += 8;
            }
            if((delta & 0b0000000000000100) == 0b0000000000000100){
                serializeUInt16(buffer+offset, (uint16)srcrect.x);
                offset += 4;
                serializeUInt16(buffer+offset, (uint16)srcrect.y);
                offset += 4;
                serializeUInt16(buffer+offset, (uint16)srcrect.h);
                offset += 4;
                serializeUInt16(buffer+offset, (uint16)srcrect.w);
                offset += 4;
            }
            return offset;
        }

        void networkUpdate(TCPsocket tcpsock){
            char buffer[20];
            strncpy(buffer, "", 20);
            SDLNet_TCP_Recv(tcpsock, buffer, 2);
            uint16 delta = network::unserializeUInt16(buffer);
            if ((delta & 0b0000000000000001) == 0b0000000000000001) {
                SDLNet_TCP_Recv(tcpsock, buffer, 8);
                position = unserializeVector(buffer);
            }
            if ((delta & 0b0000000000000010) == 0b0000000000000010) {
                SDLNet_TCP_Recv(tcpsock, buffer, 8);
                velocity = unserializeVector(buffer);
            }
            if ((delta & 0b0000000000000100) == 0b0000000000000100) {
                SDLNet_TCP_Recv(tcpsock, buffer, 4);
                srcrect.x = network::unserializeUInt16(buffer);
                SDLNet_TCP_Recv(tcpsock, buffer, 4);
                srcrect.y = network::unserializeUInt16(buffer);
                SDLNet_TCP_Recv(tcpsock, buffer, 4);
                srcrect.w = network::unserializeUInt16(buffer);
                SDLNet_TCP_Recv(tcpsock, buffer, 4);
                srcrect.h = network::unserializeUInt16(buffer);
            }
        }

        EntityState(uint32 id, math::Vector2 position, math::Vector2 velocity, SDL_Rect srcrect)
            : id(id), position(position), velocity(velocity), srcrect(srcrect){}
    };
}

#endif //GAME_MP_SERVER_ENTITYSTATE_H
