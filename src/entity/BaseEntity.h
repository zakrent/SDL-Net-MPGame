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
        uint32 id;
        math::Vector2 position;
        math::Vector2 lastPos;
        math::Vector2 velocity;
        float colliderRadius;
        SDL_Rect srcrect;

        void updatePhysics();

    public:
        bool active;
        bool shouldBeDestroyed;

        uint32 getID(){return id;}
        void setVelocity(const math::Vector2 &_velocity){velocity = _velocity;}
        math::Vector2 getPosition(){return position;}
        float getColliderRadius(){return colliderRadius;}

        virtual void update();
        virtual void handleCollision();
        virtual network::EntityState generateEntityState();
        BaseEntity(math::Vector2 position, math::Vector2 velocity, SDL_Rect srcrect);
    };
}

#endif //GAME_MP_SERVER_BASEENTITY_H
