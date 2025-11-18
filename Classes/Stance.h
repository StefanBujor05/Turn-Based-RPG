#ifndef STANCE_H
#define STANCE_H

#include <iostream>

class Stance {

    int bonusDamage = 0;

public:
    Stance();

    [[nodiscard]] int getBonusDamage() const;
    void increaseBonusDamage(const int amount);
    void resetBonusDamage();

    friend std::ostream& operator<<(std::ostream& os, const Stance& s);
};

#endif // STANCE_H