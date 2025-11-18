//
// Created by bujor on 11/18/2025.
//

#ifndef STATUSEFFECT_H
#define STATUSEFFECT_H

#include <iostream>
#include "enums.h"

class StatusEffect {

    statusEffectType effectType;
    int damage;
    mutable int duration;

public:

    StatusEffect(statusEffectType effectType, int damage, int duration);

    [[nodiscard]]statusEffectType getEffectType() const;

    [[nodiscard]]int getEffectDamage() const;
    [[nodiscard]]int getEffectDuration() const;

    // void incrementEffectDamage(int amount) {
    //     damage += amount;
    // }

    void decrementEffectDuration() const;

    friend std::ostream& operator<<(std::ostream& os, const StatusEffect& obj);

};

#endif //STATUSEFFECT_H
