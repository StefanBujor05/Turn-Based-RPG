//
// Created by bujor on 12/23/2025.
//

#ifndef ARCHER_H
#define ARCHER_H

#include "Threshold.h"
#include "RNG.h"
#include "Attack.h"
#include "Entity.h"


class Archer: public Entity{

    Threshold<int> criticalThreshold = MakeThreshold(10); // roll d20
    Threshold<int> hiddenThreshold = MakeThreshold(10);
    //float criticalRoll;
    int criticalDamage = 1;
    bool hidden = false;
    int critChanceBonus = 0;

public:

    Archer(const std::string &name, int healthPoints, int maxHealthPoints);

    void takeDamage(const Attack& attack) override;

    void hide();
    Attack arrowShot();
    Attack poisonArrow();
    void elvenHealing();

    ~Archer() override;


};



#endif //ARCHER_H
