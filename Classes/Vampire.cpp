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

    // ABILITIES -----------------------------------------------------------------------
Attack Vampire::fangBite(){
    // deal damage and heal
    // doubled when below 50% hp
    Attack attack(damageType::Piercing, 1);
    int healAmount = 1;

    std::cout<<getName()<<" used Fang Bite!\n";

    if (getHealthPoints() < getMaxHealthPoints()/2) {
        healAmount = healAmount * 2;
        std::cout<<getName()<<" healed for "<<healAmount<<" HP!\n";
        attack.increaseDamage(1);
    }

    heal(healAmount); // Healing happens regardless of bonus damage, just amount changes

    return attack;
}

Attack Vampire::bloodSplatter() {
    // splatters blood on opponent
    // if bellow half hp the blood infects the opponent,
    // dealing extra damage
    Attack attack(damageType::Blood, 1);

    int infectedDamage = 0;

    std::cout<<getName()<<" used Blood Splatter!\n";

    if (getHealthPoints() < getMaxHealthPoints()/2) {
        //infectedDamage = 1;

        StatusEffect effect = {statusEffectType::Poisoned, 1, 2};
        attack.setEffect(effect);

        std::cout<<"...and it poisons the enemy!\n";
    }

    attack.increaseDamage(infectedDamage) ;

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

}

Attack Vampire::bloodTransfusion() {

    // can only be used when 1hp
    // deals very high blood dmg
    Attack attack(damageType::Blood, 4);

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

}

Vampire::~Vampire() = default;

