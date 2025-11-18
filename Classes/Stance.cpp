//
// Created by bujor on 11/18/2025.
//

#include "Stance.h"

    Stance::Stance() = default;

    [[nodiscard]] int Stance::getBonusDamage() const {
        return bonusDamage;
    }
    void Stance::increaseBonusDamage(const int amount) {
        bonusDamage += amount;
    }
    void Stance::resetBonusDamage() {
        bonusDamage = 0;
    }




std::ostream& operator<<(std::ostream& os, const Stance& s) {
        if (s.bonusDamage > 0) {
            os <<s.bonusDamage << " bonus DMG";
        } else {
            os << "Normal";
        }
        return os;
    }
