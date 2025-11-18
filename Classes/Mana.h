//
// Created by bujor on 11/18/2025.
//

#ifndef MANA_H
#define MANA_H

#include<iostream>

class Mana {

    int currentMana;
    const int totalMana;

public:

    [[nodiscard]]int getMana() const;
    [[nodiscard]]int getTotalMana() const;

    void regenMana(int value);
    Mana(int mana, int totalMana);

    friend std::ostream& operator<<(std::ostream& os, const Mana& m);
};


#endif //MANA_H
