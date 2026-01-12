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

void Viking::displayUniqueStats() {
    printRage();
}

void Viking::displayAbilityDescriptions() const {
    std::cout<<"Ability descriptions:\n";
    std::cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    std::cout<<"- Rage passive: Dealing damage increases rage. Upon reaching it's threshold,"
               "damaging abilities are enchanced, but supportive ones are disabled\n";
    std::cout<<"\n";
    std::cout<<"- Ancestral scream: Call upon your ancestors to protect you, reducing "
               "the damage of the next 2 incoming attacks\n";
    std::cout<<"\n";
    std::cout<<"- Axe chop: Slam your axe into the enemy and cause them to bleed.\n";
    std::cout<<"\n";
    std::cout<<"- Spirit Sweep: Slash the enemy with a spiritual axe, dealing magic damage.\n";
    std::cout<<"\n";
    std::cout<<"- Healing prayer: A standard prayer that heals 2 HP.\n";
    std::cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
}


void Viking::performAction(Entity &enemy) {

    int playerChoice;
    std::cout << "1. Ancestral Scream\n2. Axe Chop \n3. Spirit Sweep\n4. Healing Prayer\n";
    std::cout<<">>";
    std::cin >> playerChoice;

    switch (playerChoice) {
        case 1: this->ancestralScream(); break;
        case 2: enemy.takeDamage(this->axeChop()); break;
        case 3: enemy.takeDamage(this->spiritSweep()); break;
        case 4: this->healingPrayer(); break;
        default: std::cout << this->getName() << " watches...\n"; break;
    }
    this->checkRage();

}

void Viking::performEnemyAction(Entity& player) {

    int enemyChoice = rng.getInt(1, 4);

    switch (enemyChoice) {
        case 1: this->ancestralScream(); break;
        case 2: player.takeDamage(this->axeChop()); break;
        case 3: player.takeDamage(this->spiritSweep()); break;
        case 4: this->healingPrayer(); break;
        default: std::cout << this->getName() << " watches...\n"; break;
    }
    this->checkRage();
}


void Viking::checkRage(){

    if (rage >= rageLimit && !enraged) {
        std::cout<<getName()<<" is enraged!\n";
        enraged = true;
    }
}


void Viking::printRage() const{
    std::cout<<"         Rage: "<<rage<<'/'<<rageLimit<<' ';
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

    if (enraged) {
        std::cout<<getName()<<" is too enraged to focus.\n";
        return;
    }

    ancestralResistance = 2;
    std::cout<<getName()<<" calls upon their ancestors, gaining a resistance buff!\n";
}

void Viking::healingPrayer() {

    if (enraged) {
        std::cout<<getName()<<" is too enraged to focus.\n";
        return;
    }

    heal(2);
    std::cout<<getName()<<" calls upon their prayer!\n";
}

Attack Viking::axeChop() {
    Attack attack(damageType::Slashing, 2);
    StatusEffect effect(statusEffectType::Bleeding, 1, 1);

    if (enraged) {
        attack.setEffect(effect);
        attack.increaseDamage(1);
    }

    if (!enraged) {
        rage+= attack.getDamage() + 1;
        if (rage > rageLimit) {
            rage = rageLimit;
        }
    }
    std::cout<<getName()<<" slams their axe!\n";
    return attack;

}

Attack Viking::spiritSweep() {
    Attack attack(damageType::Magic, 2);

    if (rage >= rageLimit) {
        attack.increaseDamage(2);
    }
    if (rage < rageLimit) {
        rage+= attack.getDamage();

        if (rage > rageLimit) {
            rage = rageLimit;
        }
    }

    std::cout<<getName()<<" slices, followed by their spirit!\n";
    return attack;
}

Viking::~Viking() = default;





