//
// Created by bujor on 11/18/2025.
//

#include "Entity.h"


    //getters
    [[nodiscard]] int Entity::getHealthPoints() const {
        return healthPoints;
    }
    [[nodiscard]] int Entity::getMaxHealthPoints() const {
        return maxHealthPoints;
    }
    [[nodiscard]] const std::string& Entity::getName() const {
        return name;
    }

    void Entity::takeEffectDamage() {
        if (status.getEffectType() != statusEffectType::None && status.getEffectDuration() > 0) {
            loseHealth(status.getEffectDamage());
            status.decrementEffectDuration();

            std::cout <<name<<" took "<<status.getEffectDamage()<<" damage"<<"\n";
        }
    }

    void Entity::setEffect(StatusEffect effect) {
        status = effect;
    }

    void Entity::increaseMaxHealthPoints(const int amount) {
        maxHealthPoints += amount;
    }

    void Entity::heal(const int healAmount) {
        if (healAmount + healthPoints > maxHealthPoints)
            healthPoints = maxHealthPoints;
        else
            healthPoints += healAmount;
    }


    void Entity::printHealthBar() const {
        std::cout<<getName()<<": \n";
        std::cout<<"Health Points: "<<healthPoints<<"/"<<maxHealthPoints<<' ';
        for (int i = 0; i < healthPoints; i++) {
            std::cout<<"|";
        }
        for (int i = 0; i < maxHealthPoints-healthPoints; i++) {
            std::cout<<".";
        }
        std::cout<<"\n";

    }
    // constructor

    Entity::Entity(const std::string &name, int healthPoints, int maxHealthPoints)
        : name(name), healthPoints(healthPoints),  maxHealthPoints(maxHealthPoints){}

    // methods

    void Entity::loseHealth(int damage) {
        if(healthPoints < damage) {
            healthPoints = 0;
        } else {
            healthPoints -= damage;
        }
    }

    //void Entity::takeDamage(const Attack& attack) = 0;

    Entity::~Entity()= default;

std::ostream& operator<<(std::ostream& os, const Entity& entity) {
    os<<entity.healthPoints<<' '<<entity.maxHealthPoints<< ' '<< entity.name<<entity.status<<' ';
    return os;
}