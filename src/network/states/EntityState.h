//
// Created by zakrent on 10/1/17.
//

#ifndef GAME_MP_SERVER_ENTITYSTATE_H
#define GAME_MP_SERVER_ENTITYSTATE_H

#include <SDL_video.h>
#include <iostream>
#include "../../misc/types.h"
#include "../../math/Vector2.h"
#include "../serialize.h"

namespace network{
    class EntityState{
        uint64 id;
        math::Vector2 position;
        math::Vector2 velocity;
        SDL_Rect srcrect;

    public:
        uint64 getId(){
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
                serializeUInt16(buffer+offset, srcrect.h);
                offset += 4;
                serializeUInt16(buffer+offset, srcrect.w);
                offset += 4;
            }
            return offset;
        }

        EntityState(uint64 id, math::Vector2 position, math::Vector2 velocity, SDL_Rect srcrect)
            : id(id), position(position), velocity(velocity), srcrect(srcrect){}
    };
}

#endif //GAME_MP_SERVER_ENTITYSTATE_H
