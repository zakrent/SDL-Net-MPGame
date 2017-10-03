//
// Created by zakrent on 9/26/17.
//
#include "BaseEntity.h"
#include "../math/random.h"

namespace entity {
    BaseEntity::BaseEntity(math::Vector2 position, math::Vector2 velocity = math::Vector2(0, 0))
            : position(position), lastPos(position), velocity(velocity), shouldBeDestroyed(false) {
        id = math::getRandomId();
    }

    void BaseEntity::updatePhysics() {
        lastPos = position;
        position += velocity;
    }

    network::EntityState BaseEntity::generateEntityState() {
        return network::EntityState(id, position, velocity, srcrect);
    }

    void BaseEntity::update() {
        updatePhysics();
    }
}