#include "Knight.h"
#include <stdio.h>
#include "Entity.h"

// Constructor Definition
Knight::Knight(const std::string &name, int healthPoints, int maxHealthPoints)
    : Entity(name, healthPoints, maxHealthPoints) {}


// takeDamage Implementation
void Knight::takeDamage(const Attack& attack) {
    int damageVal = attack.getDamage(); 
    StatusEffect effect = attack.getStatusEffect();

    if (attack.isActive() == false) {
        return;
    }

    // Resistance/Weakness logic
    if (attack.getType() == damageType::Normal    ||
        attack.getType() == damageType::Slashing  ||
        attack.getType() == damageType::Piercing) {

        std::cout<<"It's not very effective!\n";
        damageVal /= 2;
    }
    else
        if (attack.getType() == damageType::Magic ||
            attack.getType() == damageType::Fire  ||
            attack.getType() == damageType::Lightning) {
            damageVal *= 2;
            std::cout << "It's super effective!\n";
        }

    if (effect.getEffectType() != statusEffectType::None) {
        setEffect(effect);
    }

    if (damageVal == 0) {
        std::cout<<"...but "<<getName()<<" isn't phased\n";
    }
    else if (damageVal > 0) {
        std::cout<<getName()<<" took "<<damageVal<<" damage!\n";
        loseHealth(damageVal);
    }
}

// Ability Definitions
Attack Knight::swordSlash() {
    Attack attack(damageType::Slashing, 2);
    if (getHealthPoints() == getMaxHealthPoints())
        attack.increaseDamage(1);

    if (currentStance.getBonusDamage() > 0) {
        attack.increaseDamage(1);
        currentStance.resetBonusDamage();
    }

    std::cout<<Knight::getName()<<" used Sword Slash!\n";
    return attack;
}

void Knight::holyVow() {
    int healAmount = 1;
    std::cout<<Knight::getName()<<" used Holy Vow!\n";
    if (getHealthPoints() == getMaxHealthPoints()) {
        increaseMaxHealthPoints(1);
    }
    heal(healAmount);
}

Attack Knight::preparationLunge() {
    Attack attack(damageType::Piercing, 1);
    std::cout<<Knight::getName()<<" used Preparation Lunge!\n";

    if (!currentStance.getBonusDamage())
        currentStance.increaseBonusDamage(1);

    return attack;
}

Attack Knight::opportunityStrike() {
    std::cout<<Knight::getName()<<" used opportunity attack!\n";
    Attack attack(damageType::Slashing, 1);

    if (currentStance.getBonusDamage()) {
        attack.increaseDamage(2 * currentStance.getBonusDamage());
        currentStance.resetBonusDamage();
        std::cout<<"...and found an opportunity!\n";
    }

    return attack;
}

// Stream Operator Definition
std::ostream& operator<<(std::ostream& os, const Knight& k) {
    // Cast to the base class (Entity) to reuse its operator<< logic
    os << static_cast<const Entity&>(k);
    os << k.currentStance << '\n';
    return os;
}

// Destructor Definition
Knight::~Knight() = default;