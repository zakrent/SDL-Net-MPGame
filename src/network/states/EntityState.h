//
// Created by zakrent on 10/1/17.
//

#ifndef GAME_MP_SERVER_ENTITYSTATE_H
#define GAME_MP_SERVER_ENTITYSTATE_H

#include <SDL_video.h>
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

        uint8 getDelta(EntityState prevState){
            bool posChanged = position == prevState.position;
            bool velChanged = velocity == prevState.velocity;
            bool sctChanged = (srcrect.w == prevState.srcrect.w && srcrect.h == prevState.srcrect.h
                               && srcrect.x == prevState.srcrect.x && srcrect.y == prevState.srcrect.y);
            uint8 delta = (uint8)(0 | ((uint8)posChanged) | ((uint8)velChanged << 1) | ((uint8)sctChanged << 2));
            return delta;
        }
        void serialize(char* buffer, uint8 delta){
            serializeUInt64(buffer, id);
            serializeUInt8(buffer, delta);
            if(delta & 1){
                serializeVector(buffer,position);
            }
            if(delta & (1 << 1)){
                serializeVector(buffer,velocity);
            }
            if(delta & (1 << 2)){
                serializeUInt32(buffer, srcrect.x);
                serializeUInt32(buffer, srcrect.y);
                serializeUInt32(buffer, srcrect.h);
                serializeUInt32(buffer, srcrect.w);
            }
        }

        EntityState(uint64 id, math::Vector2 position, math::Vector2 velocity, SDL_Rect srcrect)
            : id(id), position(position), velocity(velocity), srcrect(srcrect){}
    };
}

#endif //GAME_MP_SERVER_ENTITYSTATE_H
