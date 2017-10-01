//
// Created by zakrent on 9/26/17.
//

#ifndef GAME_MP_SERVER_BASEENTITY_H
#define GAME_MP_SERVER_BASEENTITY_H

#include "../math/Vector2.h"
#include "../misc/types.h"
#include "../network/states/EntityState.h"
#include <SDL.h>
#include <SDL_video.h>

namespace entity {
    class BaseEntity {
    protected:
        uint64 id;
        math::Vector2 position;
        math::Vector2 lastPos;
        math::Vector2 velocity;
        float colliderRadius;
        SDL_Rect srcrect;

        void updatePhysics();

    public:
        bool shouldBeDestroyed;

        virtual void update() {};
        virtual network::EntityState generateEntityState();
        BaseEntity(math::Vector2 position, math::Vector2 velocity);
    };
}

#endif //GAME_MP_SERVER_BASEENTITY_H
