//
// Created by zakrent on 9/26/17.
//

#ifndef GAME_MP_SERVER_RANDOM_H
#define GAME_MP_SERVER_RANDOM_H

#include <random>

namespace math {

    std::random_device generator;

    int randomInt(int _min, int _max) {
        int min = _min;
        int max = _max;
        std::uniform_int_distribution<int> intDistribution(min, max);
        return intDistribution(generator);
    }


}

#endif //GAME_MP_SERVER_RANDOM_H
