//
// Created by bujor on 11/18/2025.
//

#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "Attack.h"
#include "Entity.h"


class Vampire : public Entity {

public:

    Vampire (const std::string &name, int healthPoints, int maxHealthPoints);

    void takeDamage(const Attack& attack)override;

    // ABILITIES -----------------------------------------------------------------------
    Attack fangBite();

    Attack bloodSplatter();

    void bloodSacrifice();

    Attack bloodTransfusion();

    ~Vampire() override;

};


#endif //VAMPIRE_H
