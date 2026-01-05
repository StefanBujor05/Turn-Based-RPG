//
// Created by bujor on 11/18/2025.
//

#ifndef ATTACK_H
#define ATTACK_H

#include <iostream>
#include "StatusEffect.h"
#include "enums.h"



class Attack {
    damageType type;
    mutable StatusEffect effect = {statusEffectType::None, 0, 0};
    int damage = 0;
    bool active = true;

public:

    //Attack (damageType type, int damage) : type(type), damage(damage){}
    Attack (damageType type, int damage);


    void increaseDamage(const int amount);

    void setEffect(StatusEffect effect_);

    void nullifiyAttack();

    // GETTERS <------------------------------->

    [[nodiscard]]bool isActive() const;
    [[nodiscard]]int getDamage() const;
    [[nodiscard]]damageType getType() const;
    [[nodiscard]]StatusEffect getStatusEffect() const;


    void decrementEffectDuration() const;
    ~Attack();
    Attack(const Attack &obj);

    Attack& operator= (const Attack& obj);

    friend std::ostream& operator<< (std::ostream& os, const Attack& obj);

};






#endif //ATTACK_H
