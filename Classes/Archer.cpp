//
// Created by bujor on 12/23/2025.
//

#include "Archer.h"

Archer::Archer(const std::string &name, int healthPoints, int maxHealthPoints)
    : Entity(name, healthPoints, maxHealthPoints){}

void Archer::takeDamage(const Attack& attack) {
    int damageVal = attack.getDamage();
    StatusEffect effect = attack.getStatusEffect();

    RNG rng = RNG();
    int hitWhileHiddenRol = rng.getInt(1, 20);

    // check if archer is hidden
    // if hidden, check if they still get hit
    if (hidden) {
        if (!hiddenThreshold.isMet(hitWhileHiddenRol)) {
            std::cout<<"...but "<<getName()<<" is hidden!\n";
            return;
        }
        damageVal++;
    }

    if (attack.isActive() == false) {
        return;
    }

    if (attack.getType() == damageType::Slashing  ||
        attack.getType() == damageType::Blood) {

        std::cout<<"It's not very effective!\n";
        damageVal /= 2;
        }
    else
        if (attack.getType() == damageType::Magic ||
            attack.getType() == damageType::Fire) {
            damageVal *= 2;
            std::cout << "It's super effective!\n";
            }

    if (effect.getEffectType() != statusEffectType::None) {
        setEffect(effect);
    }

    if (damageVal == 0) {
        std::cout<<"...but "<<getName()<<" isn't affected\n";
    }
    else if (damageVal > 0) {
        hidden = false;
        std::cout<<getName()<<" took "<<damageVal<<" damage!\n";
        loseHealth(damageVal);
    }

}

void Archer::hide() {
    hidden = true;
    std::cout<<getName()<<" is hidden!\n";
}

void Archer::elvenHealing() {
    healStatus();
    heal(2);
    std::cout<<getName()<<" healed and cleansed all status effects!\n";
}

Attack Archer::arrowShot() {

    Attack attack(damageType::Piercing, 2);

    std::cout<<getName()<<" fired an arrow!\n";

    if (hidden) {
        critChanceBonus = 5;
        hidden = false;
        std::cout<<getName()<<" came out of hiding!\n";
    }

    int critical = RNG().getInt(1, 20) + critChanceBonus;
    if (criticalThreshold.isMet(critical)) {
        attack.increaseDamage(criticalDamage);
        std::cout<<"It's a crit!\n";
    }

    critChanceBonus = 0;
    return attack;
}

Attack Archer::poisonArrow() {

    Attack attack(damageType::Piercing, 1);
    StatusEffect effect(statusEffectType::Poisoned, 1, 2);
    attack.setEffect(effect);

    std::cout<<getName()<<" fired a poison arrow!\n";

    if (hidden) {
        critChanceBonus = 5;
        hidden = false;
        std::cout<<getName()<<" came out of hiding!\n";
    }

    int critical = RNG().getInt(1, 20) + critChanceBonus;
    if (criticalThreshold.isMet(critical)) {
        attack.increaseDamage(criticalDamage);
        std::cout<<"It's a crit!\n";
    }

    critChanceBonus = 0;
    return attack;
}


Archer::~Archer() = default;