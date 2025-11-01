/*
 * Bujor Stefan
 * Proiect POO - Turn-Based RPG (nume temporar)
*/
#include<iostream>
#include<random>
#include<ctime>
#include <memory>

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
    [[nodiscard]] const std::string& getName() const {
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
        } else {
            healthPoints -= damage;
        }
    }

    friend std::ostream& operator<<(std::ostream &os, const Entity &e);

    virtual void takeDamage(const Attack& attack) = 0;

    virtual ~Entity()= default;
};

std::ostream& operator<<(std::ostream& os, const Entity& entity) {
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


    void takeDamage(const Attack& attack) override{
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
                std::cout << "It's super effective!\n";
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

    Attack opportunityStrike() {

        // strikes the opponent dealing slashing damage
        // if positioned properly, double the bonus damage

        std::cout<<Knight::getName()<<" used opportunity attack!\n";
        Attack attack(damageType::Slashing, 1);

        if (getBonusDamage()) {
            attack.increaseDamage(2*getBonusDamage());
            resetBonusDamage();
            std::cout<<"...and found an opportunity!\n";
        }

        return attack;
    }



    ~Knight() override = default;
};


class Vampire : public Entity {

public:

    Vampire (const std::string &name, int healthPoints, int maxHealthPoints)
            : Entity(name, healthPoints, maxHealthPoints) {}

    void takeDamage(const Attack& attack) override{
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
        else {
            std::cout<<getName()<<" took "<<damageVal<<" damage!\n";
            loseHealth(damageVal);
        }


    }

    // ABILITIES -----------------------------------------------------------------------
    Attack fangBite(){
        // deal damage and heal
        // doubled when below 50% hp
        Attack attack(damageType::Piercing, 1);
        int healAmount = 1;

        std::cout<<getName()<<" used Fang Bite!\n";

        if (getHealthPoints() < getMaxHealthPoints()/2) {
            healAmount = healAmount * 2;
            std::cout<<getName()<<" healed for "<<healAmount<<" HP!\n";
            attack.increaseDamage(1);
        }

        heal(healAmount); // Healing happens regardless of bonus damage, just amount changes

        return attack;
    }

    Attack bloodSplatter() {
        // splatters blood on opponent
        // if bellow half hp the blood infects the opponent,
        // dealing extra damage
        Attack attack(damageType::Blood, 1);
        int infectedDamage = 0;

        std::cout<<getName()<<" used Blood Splatter!\n";

        if (getHealthPoints() < getMaxHealthPoints()/2) {
            infectedDamage = 1;
            std::cout<<"...and it infects the enemy!\n";
        }

        attack.increaseDamage(infectedDamage) ;

        return attack;
    }

    void bloodSacrifice() {

        // Unless it will kill you, sacrifice 2 hp
        if (getHealthPoints() > 2) {
            loseHealth(2);
            std::cout<<getName()<<" sacrficied 2 HP!\n";
        }
        else
            std::cout<<getName()<<" attemped a blood sacrifice\n ...but it failed.\n";

    }

    Attack bloodTransfusion() {

        // can only be used when 1hp
        // deals very high blood dmg
        Attack attack(damageType::Blood, 4);

        if (getHealthPoints() == 1) {
            std::cout<<getName()<<" used their last bit of strength!\n";
            return attack;
        }

        attack.increaseDamage(-4);
        std::cout<<getName()<<" attempted a blood transfusion...\n...but is not yet strong enough\n";
        return attack;

    }

    ~Vampire() override = default;

};

class Wizard : public Entity {
    const int totalMana;
    int mana;

public:

    Wizard(const std::string &name, int healthPoints, int maxHealthPoints, int mana, int totalMana)
        : Entity(name, healthPoints, maxHealthPoints), totalMana(totalMana), mana(mana) {}

    [[nodiscard]] int getMana() const {
        return mana;
    }

    [[nodiscard]] int getTotalMana() const {
        return totalMana;
    }

    void regenMana(int value) {
        mana += value;
        if (mana > totalMana) mana = totalMana;
        if (mana < 0) mana = 0;
    }

    void printMana() const{
        std::cout<<"Mana: "<<mana<<'/'<<totalMana;
        for (int i = 0; i < getMana(); i++) {
            std::cout<<'|';
        }
        for (int i = 0; i < getTotalMana() - getMana(); i++) {
            std::cout<<'.';
        }
        std::cout<<'\n';
    }

    void takeDamage(const Attack &attack) override {

        int damageVal = attack.getDamage();

        if (attack.getType() == damageType::Slashing ||
            attack.getType() == damageType::Piercing   ) {
            damageVal*=2;
            std::cout << "It's super effective!\n";
        }

        if (attack.getType() == damageType::Holy ||
            attack.getType() == damageType::Blood  ) {
            damageVal/=2;
            std::cout << "It's not very effective!\n";
        }

        if (damageVal <= 0) {
            damageVal = 0;
            std::cout<<"...but "<<getName()<<" isn't affected!\n";
        }
        else {
            std::cout<<getName()<<" has taken "<<damageVal<<" damage!\n";
            loseHealth(damageVal);
        }
    }

    // ABILITIES ---------------------------------------------->

    Attack magicMissile() {

        //consume 1 mana and deal 2 damage
        Attack attack(damageType::Magic, 2);

        std::cout<<getName()<<" cast Magic Missle\n";

        if (getMana() < 1) {
            attack.increaseDamage(-2);
            std::cout<<"...but is out of mana\n";
        } else {
            regenMana(-1);
        }

        return attack;
    }

    Attack bluntStaff() {
        // deals 1 damage regardless of mana
        std::cout<<getName()<<" used Blunt Staff\n";
        Attack attack(damageType::Normal, 1);
        return attack;
    }

    ~Wizard() override = default;

};


class TurnBasedRPG {
private:

    std::unique_ptr<Entity> player1;
    std::unique_ptr<Entity> player2;
    int playerTurn = 0; // 0 = player1, 1 = player2

    void displayStats() const {
        std::cout << "\n--- Current Battle Status ---\n";
        player1->printHealthBar();
        if (const auto* wizard = dynamic_cast<Wizard*>(player1.get())) {
            wizard->printMana();
        }
        player2->printHealthBar();
        if (const auto* wizard = dynamic_cast<Wizard*>(player2.get())) {
            wizard->printMana();
        }
        std::cout << "-----------------------------\n";
    }

    void playerAction() {
        int playerChoice;
        std::cout<<"Choose an attack for "<< player1->getName()<<": \n";

        if (dynamic_cast<Knight*>(player1.get())) {
            std::cout << "1. Sword Slash\n2. Preparation Lunge\n3. Holy Vow\n4. Opportunity Strike \n";
        } else if (dynamic_cast<Vampire*>(player1.get())) {
            std::cout << "1. Fang Bite\n2. Blood Splatter\n3. Blood Transfusion\n4. Blood Sacrifice\n";
        } else if (dynamic_cast<Wizard*>(player1.get())) {
            std::cout << "1. Magic Missile\n2. Blunt Staff\n3. TODO (Placeholder)\n4. TODO (Placeholder)\n";
        }

        std::cout<<">> ";
        std::cin>>playerChoice;

        if (auto* knight = dynamic_cast<Knight*>(player1.get())) {
            switch (playerChoice) {
                case 1: player2->takeDamage(knight->swordSlash()); break;
                case 2: player2->takeDamage(knight->preparationLunge()); break;
                case 3: knight->holyVow(); break;
                case 4: player2->takeDamage(knight->opportunityStrike()); break;
                default: std::cout << knight->getName() << " stands firmly!\n"; break;
            }
        } else if (auto* vampire = dynamic_cast<Vampire*>(player1.get())) {
            switch (playerChoice) {
                case 1: player2->takeDamage(vampire->fangBite()); break;
                case 2: player2->takeDamage(vampire->bloodSplatter()); break;
                case 3: player2->takeDamage(vampire->bloodTransfusion()); break;
                case 4: vampire->bloodSacrifice(); break;
                default: std::cout << vampire->getName() << " waits...\n"; break;
            }
        } else if (auto* wizard = dynamic_cast<Wizard*>(player1.get())) {
            switch (playerChoice) {
                case 1: player2->takeDamage(wizard->magicMissile()); break;
                case 2: player2->takeDamage(wizard->bluntStaff()); break;
                default: std::cout << wizard->getName() << " is concentrating on other matters\n"; break;
            }
        }
    }

    void enemyAction() {
        int player2Choice;
        srand(time(nullptr));
        player2Choice = rand()%4 + 1;

        std::cout << player2->getName() << "'s turn!\n";

        if (auto* knight = dynamic_cast<Knight*>(player2.get())) {
            switch (player2Choice) {
                case 1: player1->takeDamage(knight->swordSlash()); break;
                case 2: player1->takeDamage(knight->preparationLunge()); break;
                case 3: knight->holyVow(); break;
                case 4: player1->takeDamage(knight->opportunityStrike()); break;
                default: std::cout << knight->getName() << " stands firmly!\n"; break;
            }
        } else if (auto* vampire = dynamic_cast<Vampire*>(player2.get())) {
            switch (player2Choice) {
                case 1: player1->takeDamage(vampire->fangBite()); break;
                case 2: player1->takeDamage(vampire->bloodSplatter()); break;
                case 3: player1->takeDamage(vampire->bloodTransfusion()); break;
                case 4: vampire->bloodSacrifice(); break;
                default: std::cout << vampire->getName() << " waits...\n"; break;
            }
        } else if (auto* wizard = dynamic_cast<Wizard*>(player2.get())) {
            switch (player2Choice) {
                case 1: player1->takeDamage(wizard->magicMissile()); break;
                case 2: player1->takeDamage(wizard->bluntStaff()); break;
                default: std::cout << wizard->getName() << " is concentrating on other matters\n"; break;
            }
        }
    }

    bool checkGameOver() const {
        if (player1->getHealthPoints() <= 0) {
            std::cout<<"\nGAME OVER! "<<player2->getName()<<" has won!\n";
            return true;
        }
        if (player2->getHealthPoints() <= 0) {
            std::cout<<"\nGAME OVER! "<<player1->getName()<<" has won!\n";
            return true;
        }
        return false;
    }

    void setupGame() {
        int classChoice;
        std::cout<<"Choose class for Player 1: \n1. Knight \n2. Vampire \n3. Wizard \nYour choice: ";
        std::cin>>classChoice;
        std::cout<<"\n";

        switch(classChoice) {
            case 1:
                player1 = std::make_unique<Knight>("Arthur", 10, 10);
                break;
            case 2:
                player1 = std::make_unique<Vampire>("Dracula", 10, 10);
                break;
            case 3:
                player1 = std::make_unique<Wizard>("Maegistus", 8, 8, 10, 10);
                break;
            default:
                std::cout<<"Invalid choice. Exiting game.\n";
                player1 = nullptr;
                return;
        }

        player2 = std::make_unique<Vampire>("Vladimir", 10, 10);
    }

public:
    TurnBasedRPG() = default;

    void runGame() {
        setupGame();

        if (!player1) {
            return; // erori la alegerea jucatorului
        }

        bool gameOver = false;
        while (!gameOver) {
            displayStats();

            if (playerTurn == 0) {
                playerAction();
            } else {
                enemyAction();
            }

            gameOver = checkGameOver();

            std::cout<<"\n-------------------------------------\n";

            playerTurn = 1 - playerTurn;
        }

    }
};



int main() {
    TurnBasedRPG game;
    game.runGame();

    return 0;
}