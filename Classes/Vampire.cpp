//
// Created by bujor on 11/18/2025.
//

#include "Vampire.h"
#include "GameExceptions.h"
#include <iostream>

Vampire::Vampire (const std::string &name, int healthPoints, int maxHealthPoints)
    : Entity(name, healthPoints, maxHealthPoints) {}

void Vampire::takeDamage(const Attack& attack) {
    int damageVal = attack.getDamage(); // initial dmg value
    StatusEffect effect = attack.getStatusEffect();

    if (attack.isActive() == false) {
        return;
    }

    // typing
    if (attack.getType() == damageType::Blood ||
        attack.getType() == damageType::Magic){

        damageVal/=2;
        std::cout << "It's not very effective!\n";
        }
    else
        if (attack.getType() == damageType:: Holy ||
            attack.getType() == damageType:: Piercing) {
            damageVal*=2;
            std::cout << "It's super effective!\n";
            }

    if (effect.getEffectType() != statusEffectType::None) {
        setEffect(effect);
    }

    if (damageVal == 0) {
        std::cout<<"...but "<<getName()<<" ignored it\n";
    }
    else {
        std::cout<<getName()<<" took "<<damageVal<<" damage!\n";
        loseHealth(damageVal);
    }

}

void Vampire::displayUniqueStats() {
    printHemorrhage();
}

void Vampire::displayAbilityDescriptions() const {
    std::cout<<"Ability descriptions:\n";
    std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout<<"<@> Hemorrhage passive: Build up hemorrhage by dealing damage. When the threshold is met,\n"
               "buff basic abilities' damage and healing effects.\n";
    std::cout<<"\n";
    std::cout<<"<@> Fang Bite: Pierce the enemy's flesh with your fangs and taking a sip of their blood,\n"
               "healing you in the process. If below half HP, double the healing.\n";
    std::cout<<"\n";
    std::cout<<"<@> Blood Splatter: Splash a chalice of blood onto your opponent. If below half HP or \n"
               "at max hemorrhage, infect the enemy with poison.\n";
    std::cout<<"\n";
    std::cout<<"<@> Blood Sacrifice: Tear a part of your flesh and lose 2 HP and increase hemorrhage.\n";
    std::cout<<"\n";
    std::cout<<"<@> Blood Transfusion: Only usable at 1 HP. Swap parts of your opponent's blood with yours,\n"
               "dealing massive damage and healing yourself\n";
    std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}


void Vampire::performAction(Entity& enemy) {

    int playerChoice;
    std::cout << "1. Fang Bite\n2. Blood Splatter\n3. Blood Transfusion\n4. Blood Sacrifice\n";
    std::cout<<">>";
    std::cin >> playerChoice;

    switch (playerChoice) {
        case 1: enemy.takeDamage(this->fangBite()); break;
        case 2: enemy.takeDamage(this->bloodSplatter()); break;
        case 3: enemy.takeDamage(this->bloodTransfusion()); break;
        case 4: this->bloodSacrifice(); break;
        default: std::cout << this->getName() << " waits...\n"; break;
    }

}

void Vampire::performEnemyAction(Entity &player) {

    int enemyChoice = rng.getInt(1, 4);

    switch (enemyChoice) {
        case 1: player.takeDamage(this->fangBite()); break;
        case 2: player.takeDamage(this->bloodSplatter()); break;
        case 3: player.takeDamage(this->bloodTransfusion()); break;
        case 4: this->bloodSacrifice(); break;
        default: std::cout << this->getName() << " waits...\n"; break;
    }

}

void Vampire::increaseHemorrhage(float value) {

    hemorrhage += value;
    if (hemorrhage > hemorrhageThreshold.getValue()) {
        hemorrhage = hemorrhageThreshold.getValue();
    }
}

void Vampire::printHemorrhage() const {
    std::cout<<"Hemorrhage: ";
    hemorrhageThreshold.printThreshold(hemorrhage);
}


    // ABILITIES -----------------------------------------------------------------------
Attack Vampire::fangBite(){
    // deal damage and heal
    // doubled when below 50% hp
    Attack attack(damageType::Piercing, 1);
    int healAmount = 1;

    if (hemorrhageThreshold.isMet(hemorrhage)) {
        hemorrhage = 0;
        attack.increaseDamage(2);
        healAmount++;
    }

    std::cout<<getName()<<" used Fang Bite!\n";

    if (getHealthPoints() < getMaxHealthPoints()/2) {
        healAmount = healAmount * 2;
        std::cout<<getName()<<" healed for "<<healAmount<<" HP!\n";
        attack.increaseDamage(1);
    }

    heal(healAmount); // Healing happens regardless of bonus damage, just amount changes

    increaseHemorrhage(4.5f);

    return attack;
}

Attack Vampire::bloodSplatter() {
    // splatters blood on opponent
    // if bellow half hp the blood infects the opponent,
    // dealing extra damage
    Attack attack(damageType::Blood, 1);

    //int infectedDamage = 0;

    if (hemorrhageThreshold.isMet(hemorrhage)) {
        hemorrhage = 0;
        StatusEffect effect = {statusEffectType::Poisoned, 1, 2};
        attack.setEffect(effect);
        attack.increaseDamage(1);
    }

    std::cout<<getName()<<" used Blood Splatter!\n";

    if (getHealthPoints() < getMaxHealthPoints()/2) {

        StatusEffect effect = {statusEffectType::Poisoned, 1, 2};
        attack.setEffect(effect);

        std::cout<<"...and it poisons the enemy!\n";
    }

    increaseHemorrhage(2.5f);

    //attack.increaseDamage(infectedDamage) ;
    return attack;
}

void Vampire::bloodSacrifice() {

    // Unless it will kill you, sacrifice 2 hp
    if (getHealthPoints() > 2) {
        loseHealth(2);
        std::cout<<getName()<<" sacrficied 2 HP!\n";
    }
    else
        std::cout<<getName()<<" attemped a blood sacrifice\n ...but it failed.\n";

    increaseHemorrhage(2.5f);

}

Attack Vampire::bloodTransfusion() {

    // can only be used when 1hp
    // deals very high blood dmg
    Attack attack(damageType::Blood, 4);
    int healAmount = 2;

    if (hemorrhageThreshold.isMet(hemorrhage)) {
        hemorrhage = 0;
        attack.increaseDamage(2);
        healAmount++;
    }

    try {
        if (getHealthPoints() > 1) throw InvalidAbilityException(" health needs to be 1");

            if (getHealthPoints() == 1) {
                std::cout<<getName()<<" used their last bit of strength!\n";
                return attack;
            }
    }
    catch (InvalidAbilityException& e) {
        attack.nullifiyAttack();
        std::cout<<getName()<<" attempted a blood transfusion...\n...but is not yet strong enough\n";
        std::cout<<e.what()<<"\n";
        return attack;
    }

    heal(healAmount);
    return attack;

}

Vampire::~Vampire() = default;

