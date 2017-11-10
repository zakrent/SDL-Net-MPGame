//
// Created by zakrent on 9/28/17.
//

#ifndef GAME_MP_SERVER_PHYSICS_H
#define GAME_MP_SERVER_PHYSICS_H

#include <cmath>
#include "Vector2.h"
#include "../entity/BaseEntity.h"

namespace math {
    inline bool checkCollision(entity::BaseEntity entity1, entity::BaseEntity entity2){
        Vector2 position1 = entity1.getPosition();
        Vector2 position2 = entity2.getPosition();
        float colliderRadius1 = entity1.getColliderRadius();
        float colliderRadius2 = entity2.getColliderRadius();
        return sqrt(pow((double)(position1.x-position2.x),2)+pow((double)(position1.y-position2.y),2)) < (colliderRadius1+colliderRadius2);
    }
}

#endif //GAME_MP_SERVER_PHYSICS_H
