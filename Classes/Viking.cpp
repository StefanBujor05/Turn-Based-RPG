//
// Created by bujor on 12/19/2025.
//

#include "Viking.h"
#include <iostream>

Viking::Viking(const std::string &name, int healthPoints, int maxHealthPoints, int rage, int ancestralResistance = 0)
    : Entity(name, healthPoints, maxHealthPoints), rage(rage), ancestralResistance(ancestralResistance) {}

void Viking::takeDamage(const Attack &attack) {
    int damageVal = attack.getDamage();
    StatusEffect effect = attack.getStatusEffect();

    if (attack.isActive() == false) {
        return;
    }

    if (attack.getType() == damageType::Holy ||
        attack.getType() == damageType::Frost){

        damageVal/=2;
        std::cout << "It's not very effective!\n";
        }
    else
        if (attack.getType() == damageType:: Magic ||
            attack.getType() == damageType:: Piercing) {
            damageVal*=2;
            std::cout << "It's super effective!\n";
            }

    if (effect.getEffectType() != statusEffectType::None) {
        setEffect(effect);
    }

    if (ancestralResistance) {
        damageVal--;
        ancestralResistance--;
    }

    if (damageVal == 0) {
        std::cout<<"...but "<<getName()<<" is unaffected\n";
    }
    else {
        std::cout<<getName()<<" took "<<damageVal<<" damage!\n";
        loseHealth(damageVal);
    }

}

void Viking::printRage() {
    std::cout<<"         Rage: "<<rage<<'/'<<rageLimit;
    for (int i = 0; i < rage; i++) {
        std::cout<<'|';
    }
    for (int i = 0; i < rageLimit - rage; i++) {
        std::cout<<'.';
    }
    std::cout<<'\n';
}


void Viking::ancestralScream() {
    // invokes past ancestors in order to grant special effect
    // next 2 attacks deal 1 less damage

    if (rage >= rageLimit) {
        std::cout<<getName()<<" is too enraged to focus.\n";
        return;
    }

    ancestralResistance = 2;
    std::cout<<getName()<<" calls upon their ancestors, gaining a resistance buff!\n";
}

void Viking::healingPrayer() {

    if (rage >= rageLimit) {
        std::cout<<getName()<<" is too enraged to focus.\n";
        return;
    }

    heal(2);
    std::cout<<getName()<<" calls upon their prayer!\n";
}

Attack Viking::axeChop() {
    Attack attack(damageType::Slashing, 2);
    StatusEffect effect(statusEffectType::Bleeding, 1, 1);

    if (rage >= rageLimit) {
        attack.setEffect(effect);
        attack.increaseDamage(1);
    }

    if (rage < rageLimit) {
        rage+= attack.getDamage();
    }
    std::cout<<getName()<<" slames their axe!\n";
    return attack;

}

Attack Viking::spiritSweep() {
    Attack attack(damageType::Magic, 2);

    if (rage >= rageLimit) {
        attack.increaseDamage(2);
    }
    if (rage < rageLimit) {
        rage+= attack.getDamage();
    }

    std::cout<<getName()<<" slices, followd by their spirits!\n";
    return attack;
}

Viking::~Viking() = default;





