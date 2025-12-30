#ifndef KNIGHT_H
#define KNIGHT_H

#include <iostream>
#include <string>
#include "Entity.h" // Base class
#include "Stance.h"
#include "Attack.h" // Required for ability return type

class Knight : public Entity {

private:
    Stance currentStance;
    //bool raisedShield = false;

public:
    // Constructor
    Knight(const std::string &name, int healthPoints, int maxHealthPoints);

    // Virtual function overridden from Entity
    void takeDamage(const Attack& attack) override; // if shield is raised, the next atk deals bonus dmg

    // Abilities (declared here, defined in .cpp)
    [[nodiscard]]Attack swordSlash();
    void holyVow();
    Attack preparationLunge();
    Attack opportunityStrike();

    // Overloaded stream operator (declared as a friend)
    friend std::ostream& operator<<(std::ostream& os, const Knight& k);

    // Virtual destructor
    ~Knight() override;
};


#endif // KNIGHT_H