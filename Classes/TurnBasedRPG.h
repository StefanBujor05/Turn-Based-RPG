//
// Created by bujor on 11/18/2025.
//

#ifndef TURNBASEDRPG_H
#define TURNBASEDRPG_H

#include "RNG.h"
#include "Entity.h"
#include <memory>

void artificialDelay();

class TurnBasedRPG {

    std::unique_ptr<Entity> player1;
    std::unique_ptr<Entity> player2;
    int playerTurn = 0; // 0 = player1, 1 = player2
    RNG rng;

    void displayStats() const;

    void playerAction();

    void enemyAction();

    bool checkGameOver() const;

    void setupGame();

public:

    TurnBasedRPG();

    void runGame();
};

#endif //TURNBASEDRPG_H
