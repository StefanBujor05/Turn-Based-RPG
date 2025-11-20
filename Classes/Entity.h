//
// Created by bujor on 11/18/2025.
//

#ifndef ENTITY_H
#define ENTITY_H

#include "Attack.h"
#include <iostream>
#include "enums.h"

class Entity {

    const std::string name;
    int healthPoints;
    int maxHealthPoints;
    static int entityCount;
    StatusEffect status = {statusEffectType::None, 0, 0};


public:

    //getters
    [[nodiscard]] int getHealthPoints() const;
    [[nodiscard]] int getMaxHealthPoints() const;
    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] int getEntityCount() const;
    void takeEffectDamage();

    void setEffect(StatusEffect effect);

    void increaseMaxHealthPoints(const int amount);

    void heal(const int healAmount);

    void printHealthBar() const;
    // constructor

    Entity(const std::string &name, int healthPoints, int maxHealthPoints);

    // methods

    void loseHealth(int damage);

    friend std::ostream& operator<<(std::ostream &os, const Entity &e);

    virtual void takeDamage(const Attack& attack)=0;

    virtual ~Entity()=0;


};



#endif //ENTITY_H
