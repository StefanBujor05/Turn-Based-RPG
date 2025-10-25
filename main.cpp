#include<iostream>
#include<random>
#include<time.h>
//#include <variant>
//#include<cstring>

void cleartty(void)
{
    fputs("\x1b[1;1H\x1b[2J", stdout);
    fflush(stdout);
}

enum class damageType{Normal, Slashing, Piercing, Magic, Blood, Holy};


class Attack {
    damageType type;
    int damage = 0;

public:

    Attack (damageType type, int damage) : type(type), damage(damage) {}

    void increaseDamage(const int amount) {
        damage += amount;
    }


    // GETTERS <------------------------------->

    [[nodiscard]]int getDamage() const{
        return damage;
    }

    [[nodiscard]]damageType getType() const {
        return type;
    }


    ~Attack()= default;
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

    friend std::ostream& operator<<(std::ostream &os, const Entity &e);

    ~Entity()= default;
};

std::ostream& operator<<(std::ostream& os, Entity& entity) {
    os<<entity.getHealthPoints()<<' '<<entity.getMaxHealthPoints()<< ' '<< entity.getName()<<'\n';
    return os;
}

class Knight : public Entity {

    int bonusDamage = 0;

public:

    Knight(const std::string &name, int healthPoints, int maxHealthPoints)
        : Entity(name, healthPoints, maxHealthPoints) {}


    [[nodiscard]] int getBonusDamage() const {
        return bonusDamage;
    }

    void increaseBonusDamage(const int amount) {
        bonusDamage += amount;
    }

    void resetBonusDamage() {
        bonusDamage = 0;
    }


    void takeDamage(const Attack& attack) {
        int damageVal = attack.getDamage(); // initial dmg value

        if (attack.getType() == damageType::Normal    ||
            attack.getType() == damageType::Slashing  ||
            attack.getType() == damageType::Piercing) {

            std::cout<<"It's not very effective!\n";
            damageVal/=2;
        }
        else
            if (attack.getType() == damageType::Magic) {
                damageVal*=2;
                std::cout << "It's super effective!";
            }

        if (damageVal == 0) {
            std::cout<<"...but "<<getName()<<" isn't phased\n";

        }
        else if (damageVal > 0) {
            std::cout<<getName()<<" took "<<damageVal<<" damage!\n";
            loseHealth(damageVal);
        }


    }

    // ABILITIES -----------------------------------------------------------------------
    [[nodiscard]]Attack swordSlash() {
        //slashes with a longSword
        Attack attack(damageType::Slashing, 1);
        if (getHealthPoints() == getMaxHealthPoints())
            attack.increaseDamage(1);


        if (getBonusDamage()) {
            attack.increaseDamage(getBonusDamage());
            resetBonusDamage();

        }

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

    Attack preparationLunge() {

        // Lunge at the enemy, dealing piercing damage and position yourself
        // Next attack is enchanced

        Attack attack(damageType::Piercing, 1);
        std::cout<<Knight::getName()<<" used Preparation Lunge!\n";

        if (!getBonusDamage())
            increaseBonusDamage(1);

        return attack;

    }

    ~Knight()= default;
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
            std::cout << "It's not very effective!\n";
            }
        else
            if (attack.getType() == damageType:: Holy ||
                attack.getType() == damageType:: Piercing) {
                damageVal*=2;
                std::cout << "It's super effective!\n";
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

        // can only be used when 1hp
        // deals very high blood dmg
        Attack attack(damageType::Blood, 3);

        if (getHealthPoints() == 1) {
            std::cout<<getName()<<" used their last strength!\n";
            return attack;
        }

        attack.increaseDamage(-4);
        std::cout<<getName()<<" attempted a blood transfusion...\n...but is not yet strong enough";
        return attack;

    }

    ~Vampire()= default;

};

int main() {

    int gameOver = 0;
    int playerTurn = 1;
    int numTurn = 1;
    time_t t;
    int playerChoice;
    int player2Choice;

    Knight player1("Arthur", 10, 10);
    Vampire player2("Vladimir", 10, 10);

    // test
    // std::cout<<player1;
    // player2.printHealthBar();
    // player2.takeDamage(player1.swordSlash());
    // player2.bloodSacrifice();
    // player2.printHealthBar();
    // player1.takeDamage(player2.fangBite());
    // player1.printHealthBar();
    // player1.holyVow();
    // player1.printHealthBar();
    // player1.takeDamage(player2.bloodTransfusion());

    // main loop
    while (!gameOver) {

        std::cout<<playerTurn<<"\n";
        player1.printHealthBar();
        player2.printHealthBar();

        // player turn
        if (playerTurn == 0) {

            std::cout<<"Choose and attack: \n";
            std::cout<<"1. Sword Slash \n2. Preparation Lunge \n3. Holy Vow \n4. TODO\n";
            std::cout<<"Your choice:  ";
            std::cin>>playerChoice;

            switch (playerChoice) {
                case 1:
                    player2.takeDamage(player1.swordSlash());
                    break;
                case 2:
                    player2.takeDamage(player1.preparationLunge());
                    break;
                case 3:
                    player1.holyVow();
                    break;
                default:
                    std::cout<<player1.getName()<<" stands firmly!\n";
                    break;

            }
        }
        // enemy turn
        else {
            srand((unsigned) time(&t));
            player2Choice = rand()%4 + 1;

            switch (player2Choice) {
                case 1:
                    player1.takeDamage(player2.fangBite());
                    break;
                case 2:
                    player1.takeDamage(player2.bloodSplatter());
                    break;
                case 3:
                    player1.takeDamage(player2.bloodTransfusion());
                    break;
                case 4:
                    player2.bloodSacrifice();
                default:
                    std::cout<<player2.getName()<<" waits menacingly...\n";
                    break;

            }

        }

        // end conditions
        if (player1.getHealthPoints() <= 0) {
            std::cout<<player2.getName()<<" has won!\n";
            gameOver = 1;
        }
        else if (player2.getHealthPoints() <= 0) {
            std::cout<<player1.getName()<<" has won!\n";
            gameOver = 1;
        }

        std::cout<<"\n-------------------------------------\n";
        if (playerTurn == 1)
            {playerTurn = 0;}
        else
            {playerTurn = 1;}
        numTurn++;


    }
    return 0;
}