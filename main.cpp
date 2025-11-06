/*
 * Bujor Stefan
 * Proiect POO - Turn-Based RPG (nume temporar)
*/
#include<iostream>
#include<random>
#include<ctime>
#include <memory>
#include<cstdlib>
#include<thread>

// void clear_screen() {
// #ifdef _WIN32
//     // For Windows (Cmd, PowerShell)
//     system("cls");
// #else
//     // For Linux, macOS, and most Unix-like systems (Bash, Zsh)
//     system("clear");
// #endif
// }


// tpyings for later classes
//---------------->
enum class damageType{Normal, Slashing, Piercing, Magic, Blood, Holy, Fire, Lightning};

enum class statusEffectType{None, Electrified, Bleeding, Poisoned, Burning};
//---------------->

void artificialDelay() {
    std::chrono::milliseconds delay_duration(500);
    for (int i = 0; i < 3; i++) {
        std::this_thread::sleep_for(delay_duration);
        std::cout << '.';
    }
    std::this_thread::sleep_for(delay_duration);
}

class StatusEffect {

    statusEffectType effectType;
    int damage;
    mutable int duration;

public:

    StatusEffect(statusEffectType effectType, int damage, int duration)
        : effectType(effectType), damage(damage), duration(duration) {}

    [[nodiscard]]statusEffectType getEffectType() const{
        return effectType;
    }

    [[nodiscard]]int getEffectDamage() const{
        return damage;
    }
    [[nodiscard]]int getEffectDuration() const{
        return duration;
    }

    // void incrementEffectDamage(int amount) {
    //     damage += amount;
    // }

    void decrementEffectDuration() const{
        duration = duration - 1;
    }

    friend std::ostream& operator<<(std::ostream& os, const StatusEffect& obj);

};

std::ostream& operator<<(std::ostream& os, const StatusEffect& obj){
    os<<obj.getEffectDamage()<<" "<<obj.getEffectDuration();
    return os;
}

class Attack {
    damageType type;
    mutable StatusEffect effect = {statusEffectType::None, 0, 0};
    int damage = 0;
    bool active = true;

public:

    //Attack (damageType type, int damage) : type(type), damage(damage){}
    Attack (damageType type, int damage) : type(type), damage(damage) {}

    void increaseDamage(const int amount) {
        damage += amount;
    }

    void setEffect(StatusEffect effect_) {
        this->effect = effect_;
    }

    void nullifiyAttack() {
        active = false;
    }

    // GETTERS <------------------------------->

    [[nodiscard]]bool isActive() const {
        return active;
    }

    [[nodiscard]]int getDamage() const{
        return damage;
    }

    [[nodiscard]]damageType getType() const {
        return type;
    }

    [[nodiscard]]StatusEffect getStatusEffect() const {
        return effect;
    }

    void decrementEffectDuration() const{
        effect.decrementEffectDuration();
    }

    ~Attack() = default;
    Attack(const Attack &obj) {
        type = obj.getType();
        damage = obj.getDamage();
    }

    Attack& operator= (const Attack& obj) {
        if (this != &obj) {
            type = obj.getType();
            damage = obj.getDamage();
        }

        return *this;
    }

    friend std::ostream& operator<< (std::ostream& os, const Attack& obj);

};

std::ostream& operator<< (std::ostream& os, const Attack& obj) {
    os << obj.getStatusEffect()<<' '<<obj.getDamage()<<std::endl;
    return os;
}


class Entity {

    const std::string name;
    int healthPoints;
    int maxHealthPoints;
    StatusEffect status = {statusEffectType::None, 0, 0};


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

    void takeEffectDamage() {
        if (status.getEffectType() != statusEffectType::None && status.getEffectDuration() > 0) {
            loseHealth(status.getEffectDamage());
            status.decrementEffectDuration();

            std::cout <<name<<" took "<<status.getEffectDamage()<<" damage"<<"\n";
        }
    }

    void setEffect(StatusEffect effect) {
        status = effect;
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
        StatusEffect effect = attack.getStatusEffect();

        if (attack.isActive() == false) {
            return;
        }

        if (attack.getType() == damageType::Normal    ||
            attack.getType() == damageType::Slashing  ||
            attack.getType() == damageType::Piercing) {

            std::cout<<"It's not very effective!\n";
            damageVal/=2;
        }
        else
            if (attack.getType() == damageType::Magic ||
                attack.getType() == damageType::Fire  ||
                attack.getType() == damageType::Lightning) {
                damageVal*=2;
                std::cout << "It's super effective!\n";
            }

        if (effect.getEffectType() != statusEffectType::None) {
            setEffect(effect);
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


        if (bonusDamage) {
            attack.increaseDamage(bonusDamage);
            bonusDamage = 0;

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
        StatusEffect effect = attack.getStatusEffect();

        if (attack.isActive() == false) {
            return;
        }

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

        if (effect.getEffectType() != statusEffectType::None) {
            setEffect(effect);
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
            //infectedDamage = 1;

            StatusEffect effect = {statusEffectType::Poisoned, 1, 2};
            attack.setEffect(effect);

            std::cout<<"...and it poisons the enemy!\n";
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

        //attack.increaseDamage(-4);
        attack.nullifiyAttack();
        std::cout<<getName()<<" attempted a blood transfusion...\n...but is not yet strong enough\n";
        return attack;

    }

    ~Vampire() override = default;

};

class Mana {

    int currentMana;
    const int totalMana;

public:

    [[nodiscard]]int getMana() const{
        return currentMana;
    }

    [[nodiscard]]int getTotalMana() const{
        return totalMana;
    }

    void regenMana(int value) {
        currentMana += value;
        if (currentMana > totalMana) currentMana = totalMana;
        if (currentMana < 0) currentMana = 0;
    }

    Mana(int mana, int totalMana) : currentMana(mana), totalMana(totalMana) {}
};

class AcademicMagic {

    int progress = 0;
    const int threshHold = 5;
    bool active = false;


    public:

    AcademicMagic(int progress, bool active): progress(progress), active(active){}

    [[nodiscard]]int getProgress() const {
        return progress;
    }

    [[nodiscard]]bool getActive() const {
        return active;
    }

    [[nodiscard]]int getThreshHold() const {
        return threshHold;
    }

    void increaseProgress(int valueAmount) {
        progress += valueAmount;
        if (progress > threshHold)
            progress = threshHold;
    }

    void activate() {
        active = true;
    }
};


class Wizard : public Entity {

    Mana manaStatus = {10, 10};
    AcademicMagic ascension = {0, false};

public:

    Wizard(const std::string &name, int healthPoints, int maxHealthPoints)
        : Entity(name, healthPoints, maxHealthPoints){}


    void printMana() {
        std::cout<<"         Mana: "<<manaStatus.getMana()<<'/'<<manaStatus.getTotalMana();
        for (int i = 0; i < manaStatus.getMana(); i++) {
            std::cout<<'|';
        }
        for (int i = 0; i < manaStatus.getTotalMana() - manaStatus.getMana(); i++) {
            std::cout<<'.';
        }
        std::cout<<'\n';
    }

    void printAscensionStatus() {
        std::cout<<"    Ascension: "<<ascension.getProgress()<<'/'<<ascension.getThreshHold()<<' ';
        for (int i = 0; i < ascension.getProgress(); i++) {
            std::cout<<'|';
        }
        for (int i = 0; i < ascension.getThreshHold() - ascension.getProgress(); i++) {
            std::cout<<'.';
        }
        std::cout<<'\n';
    }

    void checkAscension() {
        if (ascension.getProgress() == ascension.getThreshHold() && !ascension.getActive()) {
            ascension.activate();
            std::cout<<getName()<<" has ascended!\n";
        }
    }

    void takeDamage(const Attack &attack) override {

        int damageVal = attack.getDamage();
        StatusEffect effect = attack.getStatusEffect();

        if (attack.isActive() == false) {
            return;
        }

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

        if (effect.getEffectType() != statusEffectType::None) {
            setEffect(effect);
        }

        if (damageVal <= 0) {
            //damageVal = 0;
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

        if (manaStatus.getMana() < 1) {
            attack.increaseDamage(-2);
            attack.nullifiyAttack();
            std::cout<<"...but is out of mana\n";
        } else {
            manaStatus.regenMana(-1);
            ascension.increaseProgress(1);
        }

        return attack;
    }

    Attack bluntStaff() {
        // deals 1 damage regardless of mana
        std::cout<<getName()<<" used Blunt Staff\n";
        Attack attack(damageType::Normal, 1);
        return attack;
    }

    Attack lightningBolt() {

        Attack attack(damageType::Lightning, 2);
        StatusEffect effect = {statusEffectType::Electrified, 1, 2};


        // if mana == 0, exit
        if (manaStatus.getMana() < 2) {
            attack.nullifiyAttack();
            std::cout<<getName()<<" tried to cast Lightning Bolt!\n";
            std::cout<<"...but is out of mana\n";
            return attack;
        }

        attack.setEffect(effect);


        manaStatus.regenMana(-2);
        ascension.increaseProgress(2);

        if (ascension.getActive() == true) {
            attack.increaseDamage(2);
            std::cout<<getName()<<" used Ascended Lightning Bolt!\n";
            std::cout<<"Enemy is electrified!\n";
            return attack;
        }

        std::cout<<getName()<<" used Lightning Bolt!\n";
        std::cout<<"Enemy is electrified!\n";
        return attack;
    }

    Attack pillarOfFire() {
        Attack attack(damageType::Fire, 2);
        StatusEffect effect = {statusEffectType::Burning, 2, 2};

        if (manaStatus.getMana() < 5) {
            attack.nullifiyAttack();
            std::cout<<getName()<<" tried to cast Pillar of Fire, but is out of mana!\n";
            return attack;
        }

        manaStatus.regenMana(-5);
        ascension.increaseProgress(5);

        if (ascension.getActive() == true) {
            attack.increaseDamage(2);
            std::cout<<getName()<<" used Ascended Pillar of Fire!\n";
            return attack;
        }

        std::cout<<getName()<<" used Pillar of Fire!\n";
        std::cout<<"Enemy is burning!\n";
        return attack;
    }

    ~Wizard() override = default;

};


class TitleScreen {


public:

    void printASCII() const{
        std::cout<<"      [\n";
        std::cout<<"<>xxxx[{::::::::::::::::::::::::> \n";
        std::cout<<"      [ \n";

        std::cout<<"           GAME TITLE\n";

        std::cout<<"                         [\n";
        std::cout<<"<::::::::::::::::::::::::[{xxxx<>\n";
        std::cout<<"                         [\n";
    }

    void printMenu() const{
        std::cout<<"\n";
        std::cout<<"[1] Start Game\n";
        std::cout<<"[2] About\n";
        std::cout<<"[3] Exit\n";
        std::cout<<">>";
    }

    void printAbout() const {
        std::cout<<"\n";
        std::cout<<"<------------- About ------------->\n\n";
        std::cout<<"Made by: Bujor Stefan\n"
                   "University of Bucharest \n"
                   "Computer Engineering \n\n";

        std::cout<<"Albums to listen to whilst playing: \n"
                   "-> Morbid Angel - Blessed are the Sick \n"
                   "-> Obituary - Cause of Death \n"
                   "-> Amon Amarth - Twilight of the Thunder Gods (for Viking class) \n"
                   "-> Morbid Angel - Formulas Fatal to the Flesh \n"
                   "-> Bolt Thrower - Those Once Loyal \n"
                   "-> Entombed - Left Hand Path \n"
                   "-> Bathory - Blood Fire Death \n\n";
        std::cout<<"[1] Back \n";
        std::cout<<">>";
    }

};

class TurnBasedRPG {

    std::unique_ptr<Entity> player1;
    std::unique_ptr<Entity> player2;
    int playerTurn = 0; // 0 = player1, 1 = player2

    void displayStats() const {
        std::cout << "\n--- Current Battle Status ---\n";
        player1->printHealthBar();
        if (auto* wizard = dynamic_cast<Wizard*>(player1.get())) {
            wizard->printMana();
            wizard->printAscensionStatus();
        }

        std::cout<<"\n";

        player2->printHealthBar();
        if (auto* wizard = dynamic_cast<Wizard*>(player2.get())) {
            wizard->printMana();
            wizard->printAscensionStatus();
        }
        std::cout << "-----------------------------\n";
    }

    void playerAction() {
        int playerChoice;


        std::cout<<"Choose an attack "<< player1->getName()<<": \n";



        if (dynamic_cast<Knight*>(player1.get())) {
            std::cout << "1. Sword Slash\n2. Preparation Lunge\n3. Holy Vow\n4. Opportunity Strike \n";
        } else if (dynamic_cast<Vampire*>(player1.get())) {
            std::cout << "1. Fang Bite\n2. Blood Splatter\n3. Blood Transfusion\n4. Blood Sacrifice\n";
        } else if (dynamic_cast<Wizard*>(player1.get())) {
            std::cout << "1. Magic Missile\n2. Blunt Staff\n3. Lightning Bolt\n4. Pillar of Fire\n";
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
                case 3: player2->takeDamage(wizard->lightningBolt()); break;
                case 4: player2->takeDamage(wizard->pillarOfFire()); break;
                default: std::cout << wizard->getName() << " is concentrating on other matters\n"; break;
            }
            wizard->checkAscension();

        }
        player1->takeEffectDamage();
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
                case 3: player1->takeDamage(wizard->lightningBolt()); break;
                case 4: player1->takeDamage(wizard->pillarOfFire()); break;
                default: std::cout << wizard->getName() << " is concentrating on other matters\n"; break;
            }
            wizard->checkAscension();
        }
        player2->takeEffectDamage();
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
        std::string playerName;

        artificialDelay();
        std::cout<<"Who are you? \n>>";
        std::cin>>playerName;
        //std::cout<<"\n";
        std::cout<<"And what is your class?: \n1. Knight \n2. Vampire \n3. Wizard \n>> ";
        std::cin>>classChoice;
        std::cout<<"\n";

        switch(classChoice) {
            case 1:
                player1 = std::make_unique<Knight>(playerName, 10, 10);
                break;
            case 2:
                player1 = std::make_unique<Vampire>(playerName, 10, 10);
                break;
            case 3:
                player1 = std::make_unique<Wizard>(playerName, 8, 8);
                break;
            default:
                std::cout<<"Invalid choice. Exiting game.\n";
                player1 = nullptr;
                return;
        }

        std::cout<<"You are playing as "<<player1->getName()<<"\n";

        player2 = std::make_unique<Wizard>("Maegistus", 8, 8);
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
                artificialDelay();
                enemyAction();
            }

            gameOver = checkGameOver();

            std::cout<<"\n-------------------------------------\n";

            playerTurn = 1 - playerTurn;

        }

    }
};



int main() {

    TitleScreen welcomeScreen;
    TurnBasedRPG game;
    int menuChoice;

    welcomeScreen.printASCII();
    welcomeScreen.printMenu();

    std::cin>>menuChoice;

    switch (menuChoice) {
        case 2:
            welcomeScreen.printAbout();
            std::cin>>menuChoice;
            [[fallthrough]];

        case 1: game.runGame();
                break;

        case 3: std::cout<<"Goodbye! ";
                exit(0);
        default: std::cout<<"Invalid choice. Exiting game.\n";
                exit(0);
    }

    return 0;
}