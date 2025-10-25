#include<iostream>
#include<random>
#include <variant>
//#include<cstring>

enum class damageType{Normal, Slashing, Piercing, Magic, Blood, Holy};

class Attack {
    damageType type;
    int damage;


public:

    Attack (damageType type, int damage) : type(type), damage(damage) {}

    void increaseDamage(const int amount) {
        damage += amount;
    }

    [[nodiscard]]int getDamage() const{
        return damage;
    }

    [[nodiscard]]damageType getType() const {
        return type;
    }
};

class Entity {

    const std::string name;
    int healthPoints;
    int maxHealthPoints;

public:

    //getters
    [[nodiscard]] int getHealthPoints() const {
        return healthPoints;
    }
    [[nodiscard]] int getMaxHealthPoints() const {
        return maxHealthPoints;
    }
    [[nodiscard]] std::string getName() const {
        return name;
    }



    void increaseMaxHealthPoints(const int amount) {
        maxHealthPoints += amount;
    }

    void heal(const int healAmount) {
        if (healAmount + healthPoints > maxHealthPoints)
            healthPoints = maxHealthPoints;
        else
            healthPoints += healAmount;
    }


    void printHealthBar() const {
        std::cout<<getName()<<": "<<healthPoints<<"/"<<maxHealthPoints<<' ';
        for (int i = 0; i < healthPoints; i++) {
            std::cout<<"|";
        }
        for (int i = 0; i < maxHealthPoints-healthPoints; i++) {
            std::cout<<".";
        }
        std::cout<<"\n";

    }
    // constructor

    Entity(const std::string &name, int healthPoints, int maxHealthPoints)
        : name(name), healthPoints(healthPoints),  maxHealthPoints(maxHealthPoints){}

    // methods

    void loseHealth(int damage) {
        if(healthPoints < damage) {
            healthPoints = 0;
        }
        healthPoints -= damage;
    }

};

class Knight : public Entity {


public:

    Knight(const std::string &name, int healthPoints, int maxHealthPoints)
        : Entity(name, healthPoints, maxHealthPoints) {}


    void takeDamage(const Attack& attack) {
        int damageVal = attack.getDamage(); // initial dmg value

        if (attack.getType() == damageType::Normal    ||
            attack.getType() == damageType::Slashing  ||
            attack.getType() == damageType::Piercing) {

            damageVal/=2;
        }
        else
            if (attack.getType() == damageType::Magic) {
                damageVal*=2;
            }

        if (damageVal == 0) {
            std::cout<<"...but "<<getName()<<" isn't phased\n";
        }
        else
            std::cout<<getName()<<" took "<<damageVal<<" damage!\n";
        loseHealth(damageVal);

    }

    // ABILITIES -----------------------------------------------------------------------
    [[nodiscard]]Attack swordSlash() const {
        //slashes with a longSword
        Attack attack(damageType::Slashing, 1);
        if (getHealthPoints() == getMaxHealthPoints())
            attack.increaseDamage(1);

        std::cout<<Knight::getName()<<" used Sword Slash!\n";
        return attack;
    }

    void holyVow() {
        // heal 1 hp
        // if hp is max, gain 1 max hp and heal
        int healAmount = 1;
        std::cout<<Knight::getName()<<" used Holy Vow!\n";
        if (getHealthPoints() == getMaxHealthPoints()) {
            increaseMaxHealthPoints(1);
        }
        heal(healAmount);
    }

};

class Vampire : public Entity {

public:

    Vampire (const std::string &name, int healthPoints, int maxHealthPoints)
            : Entity(name, healthPoints, maxHealthPoints) {}

    void takeDamage(const Attack& attack) {
        int damageVal = attack.getDamage(); // initial dmg value

        // typing
        if (attack.getType() == damageType::Blood ||
            attack.getType() == damageType::Magic){

            damageVal/=2;
            }
        else
            if (attack.getType() == damageType:: Holy ||
                attack.getType() == damageType:: Piercing) {
                damageVal*=2;
            }

        if (damageVal == 0) {
            std::cout<<"...but "<<getName()<<" ignored it\n";
        }
        else
            std::cout<<getName()<<" took "<<damageVal<<" damage!\n";
        loseHealth(damageVal);

    }

    // ABILITIES -----------------------------------------------------------------------
    Attack fangBite(){
        // deal damage and heal
        // doubled when below 50% hp
        Attack attack(damageType::Piercing, 1);
        int healAmount = 1;

        std::cout<<getName()<<" used Fang Bite!\n";

        if (getHealthPoints() < getMaxHealthPoints()/2) {
            heal(2*healAmount);
            std::cout<<getName()<<" healed for "<<healAmount<<" HP!\n";
            attack.increaseDamage(1);
            return attack;
        }

        return attack;
    }

    Attack bloodSplatter() {
        // splatters blood on opponent
        // if bellow half hp the blood infects the opponent,
        // dealing extra damage
        Attack attack(damageType::Blood, 1);
        int infectedDamage = 0;

        if (getHealthPoints() < getMaxHealthPoints()/2) {
            infectedDamage = 1;
        }

        attack.increaseDamage(infectedDamage) ;

        return attack;
    }

    void bloodSacrifice() {

        // Unless it will kill you, sacrifice 2 hp
        if (getHealthPoints() > 2) {
            heal(-2);
            std::cout<<getName()<<" sacrficied 2 HP!\n";
        }
        else
            std::cout<<getName()<<" attemped a blood sacrifice\n ...but it failed.\n";

    }

    Attack bloodTransfusion() {

        Attack attack(damageType::Blood, 3);



    }

};

int main() {

    int gameOver = 0;
    int playerTurn = 0;
    int numTurn = 1;
    Knight player1("Arthur", 10, 10);
    Vampire player2("Vladimir", 10, 10);

    player2.printHealthBar();
    player2.takeDamage(player1.swordSlash());
    player2.bloodSacrifice();
    player2.printHealthBar();
    player1.takeDamage(player2.fangBite());
    player1.printHealthBar();
    player1.holyVow();
    player1.printHealthBar();

    // main loop
    while (!gameOver) {
        // player turn
        if (playerTurn == 0) {

        }
        // enemy turn
        else {

        }


        if (player1.getHealthPoints() == 0 || player2.getHealthPoints() == 0) {
            gameOver = 1;
        }


        numTurn++;
    }
    return 0;
}