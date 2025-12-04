//
// Created by bujor on 11/20/2025.
//

#include "Blacksmith.h"
#include "Attack.h"


Blacksmith::Blacksmith(const std::string &name, int healthPoints, int maxHealthPoints, weapons w, int enhancement = 0, int armour= 0)
    : Entity(name, healthPoints, maxHealthPoints), weapon(w), enhancement(enhancement), armour(armour) {}


void Blacksmith::takeDamage(const Attack& attack) {
    int damageVal = attack.getDamage();
    StatusEffect effect = attack.getStatusEffect();

    if (attack.isActive() == false) {
        return;
    }

    if (attack.getType() == damageType::Normal    ||
        attack.getType() == damageType::Slashing  ||
        attack.getType() == damageType::Piercing  ||
        attack.getType() == damageType::Holy) {

        std::cout<<"It's not very effective!\n";
        damageVal /= 2;
        }
    else
        if (attack.getType() == damageType::Magic ||
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

        if (armour > 0) {
            if (damageVal <= armour) {
                armour -= damageVal;
                damageVal = 0;
            }
            else {
                damageVal -= armour;
                armour = 0;
            }
        }

        if (damageVal > 0) loseHealth(damageVal);
    }
}

[[nodiscard]] weapons Blacksmith::getWeapon() const {
    return weapon;
}

void Blacksmith::printStats() const{
    std::cout<<"       Armour: "<<armour<<"/2 ";
    for (int i = 0; i < armour; i++) {
        std::cout<<"|";
    }
    for (int i = 0; i < 2-armour; i++) {
        std::cout<<".";
    }
    std::cout<<"\n";
    std::cout<<"Weapon: ";
    switch (weapon) {
        case weapons::None:
            std::cout<<"None";
            break;
        case weapons::Claymore:
            std::cout<<"Claymore";
            break;
        case weapons::Hammer:
            std::cout<<"Hammer";
            break;
        case weapons::Axe:
            std::cout<<"Axe";
            break;
        default:
            std::cout<<"Unknown";
    }
    std::cout<<"\n";
}


void Blacksmith::chooseWeapon() {

    int weaponChoice = 0;
    std::cout<<"Choose the weapon you wish to craft: \n"
               "1. Claymore  2. Hammer  3. Axe\n"
               ">>";
    std::cin>>weaponChoice;

    switch (weaponChoice) {
        case 1:
            std::cout<<getName()<<" forged a deadly claymore!\n";
            enhancement = 0;
            weapon = weapons::Claymore;
            break;
        case 2:
            std::cout<<getName()<<" forged a colossal hammer!\n";
            enhancement = 0;
            weapon = weapons::Hammer;
            break;
        case 3:
            std::cout<<getName()<<" forged a heavy, engraved axe!\n";
            enhancement = 0;
            weapon = weapons::Axe;
            break;
        default:
            std::cout<<"Forging is an act of masterful cratfsmanship. \n"
                       "As such, "<<getName()<<" is not in a rush.\n";
    }

}

void Blacksmith::echanceWeapon() {

    if (weapon == weapons::None) return;

    if (enhancement < 3) {
        enhancement++;
        std::cout<<getName()<<" enhanced their weapon!\n";
        return;
        }

    std::cout<<getName()<<"'s weapon is fully enhanced already!\n";

    }


void Blacksmith::enhanceArmour() {

    if (armour > 1) return;

    armour = 2;
    std::cout<<getName()<<" forged a stronger set of armour!\n";

}

Attack Blacksmith::weaponAttack() {

    if (weapon == weapons::None) {
        Attack attack(damageType::Normal, 1);
        std::cout<<getName()<<" uses their fists to attack!\n";
        return attack;
    }
    if (weapon == weapons::Claymore) {
        Attack attack(damageType::Slashing, 2);
        StatusEffect effect(statusEffectType::Bleeding, 1, 2);

        if (armour > 0)attack.increaseDamage(1);

        attack.setEffect(effect);
        std::cout<<getName()<<" slashes with the claymore!\n";
        return attack;
    }
    if (weapon == weapons::Hammer) {
        Attack attack(damageType::Normal, 4);
        std::cout<<getName()<<" smashes with the hammer!\n";
        return attack;
    }
    if (weapon == weapons::Axe) {
        Attack attack(damageType::Slashing, 3);
        StatusEffect effect(statusEffectType::Bleeding, 2, 1);
        attack.setEffect(effect);
        std::cout<<getName()<<" slashes with the claymore!\n";
        return attack;
    }

}

Blacksmith::~Blacksmith() = default;