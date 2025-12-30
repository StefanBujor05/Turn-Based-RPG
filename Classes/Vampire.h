//
// Created by bujor on 11/18/2025.
//

#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "Attack.h"
#include "Entity.h"
#include "Threshold.h"

class Vampire : public Entity {

    Threshold<float> hemorrhageThreshold = MakeThreshold(10.0f);
    float hemorrhage = 0.0f;

public:

    Vampire (const std::string &name, int healthPoints, int maxHealthPoints);

    void takeDamage(const Attack& attack)override;

    void increaseHemorrhage(float value);
    void printHemorrhage()const;

    // ABILITIES -----------------------------------------------------------------------
    Attack fangBite();
    Attack bloodSplatter();
    void bloodSacrifice();
    Attack bloodTransfusion();

    ~Vampire() override;

};


#endif //VAMPIRE_H
