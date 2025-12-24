//
// Created by bujor on 11/18/2025.
//

#include "RNG.h"
#include <chrono>

#include <random>

    RNG::RNG() {
        engine.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    }

    int RNG::getInt(int min, int max) {

        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(engine);
    }


