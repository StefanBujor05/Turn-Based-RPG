//
// Created by bujor on 11/18/2025.
//

#ifndef WIZARD_H
#define WIZARD_H

#include <iostream>
#include <string>
#include "Entity.h"
#include "Mana.h"
#include "AcademicMagic.h"
#include <vector>


class Wizard : public Entity {

    Mana manaStatus = {10, 10};
    AcademicMagic ascension = {0, false};
    std::vector<std::string> quickSpells;

    Attack qFireBolt();
    Attack qElectricShock();
    Attack qIceSpike();


public:

    Wizard(const std::string &name, int healthPoints, int maxHealthPoints);

    void performAction(Entity &enemy) override;
    void performEnemyAction(Entity& player) override;
    void displayUniqueStats() override;

    void printMana();

    void printAscensionStatus();

    void checkAscension();

    void takeDamage(const Attack &attack) override;

    // ABILITIES ---------------------------------------------->

    Attack quickSpell();

    Attack magicMissile();

    Attack bluntStaff();

    Attack lightningBolt();

    Attack pillarOfFire();

    friend std::ostream& operator<<(std::ostream& os, const Wizard& w);

    ~Wizard() override;

};


#endif //WIZARD_H
