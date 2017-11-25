//
// Created by zakrent on 11/25/17.
//

#include "PlayerEntity.h"

entity::PlayerEntity::PlayerEntity(const math::Vector2 &position, const math::Vector2 &velocity,
                                   const SDL_Rect &srcrect) : BaseEntity(position, velocity, srcrect) {}
