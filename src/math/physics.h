//
// Created by zakrent on 9/28/17.
//

#ifndef GAME_MP_SERVER_PHYSICS_H
#define GAME_MP_SERVER_PHYSICS_H

#include <cmath>
#include "Vector2.h"

namespace math {
    bool checkCollision(Vector2 position1, float colliderRadius1, Vector2 position2, float colliderRadius2){
        return sqrt(pow((double)(position1.x-position2.x),2)+pow((double)(position1.y-position2.y),2)) < (colliderRadius1+colliderRadius2);
    }
}

#endif //GAME_MP_SERVER_PHYSICS_H
