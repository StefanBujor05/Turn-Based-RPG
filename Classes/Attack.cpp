//
// Created by bujor on 11/18/2025.
//

#include "Attack.h"


    Attack::Attack (damageType type, int damage) : type(type), damage(damage) {}

    void Attack::increaseDamage(const int amount) {
        damage += amount;
    }

    void Attack::setEffect(StatusEffect effect_) {
        this->effect = effect_;
    }

    void Attack::nullifiyAttack() {
        Attack::active = false;
    }

    // GETTERS <------------------------------->

    [[nodiscard]]bool Attack::isActive() const {
        return Attack::active;
    }

    [[nodiscard]]int Attack::getDamage() const{
        return Attack::damage;
    }

    [[nodiscard]]damageType Attack::getType() const {
        return Attack::type;
    }

    [[nodiscard]]StatusEffect Attack::getStatusEffect() const {
        return effect;
    }

    void Attack::decrementEffectDuration() const{
        effect.decrementEffectDuration();
    }

    Attack::~Attack() = default;
    Attack::Attack(const Attack &obj) {
        type = obj.getType();
        damage = obj.getDamage();
    }

    Attack& Attack::operator= (const Attack& obj) {
        if (this != &obj) {
            type = obj.type;
            damage = obj.damage;

        }
        return *this;
    }

std::ostream& operator<< (std::ostream& os, const  Attack& obj) {
        os << obj.damage<<' '<<obj.effect<<std::endl;
        return os;
    }

