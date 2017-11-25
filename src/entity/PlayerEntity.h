//
// Created by zakrent on 11/25/17.
//

#ifndef GAME_MP_SERVER_PLAYERENTITY_H
#define GAME_MP_SERVER_PLAYERENTITY_H

#include "BaseEntity.h"

namespace entity {
    class PlayerEntity : public BaseEntity{
    public:
        PlayerEntity(const math::Vector2 &position, const math::Vector2 &velocity, const SDL_Rect &srcrect);
    };
}


#endif //GAME_MP_SERVER_PLAYERENTITY_H
