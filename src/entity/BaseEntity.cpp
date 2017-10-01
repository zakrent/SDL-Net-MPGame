//
// Created by zakrent on 9/26/17.
//
#include "BaseEntity.h"

namespace entity {
    BaseEntity::BaseEntity(math::Vector2 position, math::Vector2 velocity = math::Vector2(0, 0))
            : position(position), lastPos(position), velocity(velocity), shouldBeDestroyed(false) {}

    void BaseEntity::updatePhysics() {
        lastPos = position;
        position += velocity;
    }
}