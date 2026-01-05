//
// Created by bujor on 11/20/2025.
//

#ifndef BLACKSMITH_H
#define BLACKSMITH_H

#include "Entity.h"
#include "enums.h"
#include "Attack.h"
#include <vector>


class Blacksmith: public Entity {

    weapons weapon;
    int enhancement;
    int armour;

    public:

    Blacksmith(const std::string &name, int healthPoints, int maxHealthPoints, weapons w, int enhancement, int armour);

    void performAction(Entity& enemy) override;
    void performEnemyAction(Entity& player) override;

    void takeDamage(const Attack& attack) override;
    void printStats ()const;

    //[[nodiscard]] weapons getWeapon() const;

    // Abilities

    void chooseWeapon();

    //void forgeWeapon();
    void echanceWeapon();
    void enhanceArmour();
    Attack weaponAttack();

    ~Blacksmith() override;

};



#endif //BLACKSMITH_H
