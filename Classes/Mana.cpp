//
// Created by bujor on 11/18/2025.
//

#include "Mana.h"


    [[nodiscard]]int Mana::getMana() const{
        return currentMana;
    }

    [[nodiscard]]int Mana::getTotalMana() const{
        return totalMana;
    }

    void Mana::regenMana(int value) {
        currentMana += value;
        if (currentMana > totalMana) currentMana = totalMana;
        if (currentMana < 0) currentMana = 0;
    }

    Mana::Mana(int mana, int totalMana) : currentMana(mana), totalMana(totalMana) {}


std::ostream& operator<<(std::ostream& os, const Mana& m) {
    os<<m.currentMana<<" "<<m.totalMana;
    return os;
}