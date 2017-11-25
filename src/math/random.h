//
// Created by zakrent on 9/26/17.
//

#ifndef GAME_MP_SERVER_RANDOM_H
#define GAME_MP_SERVER_RANDOM_H

#include <random>
#include <ctime>
#include "../misc/types.h"

namespace math {

    inline int randomInt(int _min, int _max) {
        std::minstd_rand rd;
        rd.seed((uint32)(std::time(nullptr)));
        int min = _min;
        int max = _max;
        std::uniform_int_distribution<int> intDistribution(min, max);
        return intDistribution(rd);
    }

    inline uint32 getRandomId(){
        return ((uint32)randomInt(0,2147483647)+(uint32)randomInt(0,2147483647));
    }

}

#endif //GAME_MP_SERVER_RANDOM_H
