//
// Created by bujor on 11/18/2025.
//

#ifndef RNG_H
#define RNG_H

#include <random>

class RNG {

    std::mt19937 engine;

public:

    RNG();

    int getInt(int min, int max);
};



#endif //RNG_H
