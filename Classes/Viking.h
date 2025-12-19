//
// Created by bujor on 12/19/2025.
//

#ifndef VIKING_H
#define VIKING_H
#include "Entity.h"


class Viking: public Entity{

    int rage;
    int rageLimit = 7;
    int ancestralResistance;

public:

    Viking(const std::string &name, int healthPoints, int maxHealthPoints, int rage, int ancestralResistance);

    void takeDamage(const Attack& attack) override;

    void printRage();

    // Attacks -------->

    void ancestralScream();
    Attack axeChop();
    Attack spiritSweep();
    void healingPrayer();


    ~Viking() override;

};



#endif //VIKING_H
