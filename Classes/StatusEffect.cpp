//
// Created by bujor on 11/18/2025.
//

#include "StatusEffect.h"
#include <iostream>


    StatusEffect::StatusEffect(statusEffectType effectType, int damage, int duration)
        : effectType(effectType), damage(damage), duration(duration) {}

    [[nodiscard]]statusEffectType StatusEffect::getEffectType() const{
        return effectType;
    }

    [[nodiscard]]int StatusEffect::getEffectDamage() const{
        return damage;
    }
    [[nodiscard]]int StatusEffect::getEffectDuration() const{
        return duration;
    }

    // void incrementEffectDamage(int amount) {
    //     damage += amount;
    // }

    void StatusEffect::decrementEffectDuration() const{
        duration = duration - 1;
        if (duration < 0) {
            duration = 0;
        }
    }


std::ostream& operator<<(std::ostream& os, const StatusEffect& obj){
    os<<obj.damage<<" "<<obj.duration<<" ";
    return os;
}
