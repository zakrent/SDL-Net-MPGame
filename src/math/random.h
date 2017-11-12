//
// Created by zakrent on 9/26/17.
//

#ifndef GAME_MP_SERVER_RANDOM_H
#define GAME_MP_SERVER_RANDOM_H

#include <random>
#include "../misc/types.h"

namespace math {

    std::random_device generator;

    int randomInt(int _min, int _max) {
        int min = _min;
        int max = _max;
        std::uniform_int_distribution<int> intDistribution(min, max);
        return intDistribution(generator);
    }

    uint32 getRandomId(){
        return ((uint32)randomInt(0,2147483647)+(uint32)randomInt(0,2147483647));
    }

}

#endif //GAME_MP_SERVER_RANDOM_H
