//
// Created by bujor on 11/18/2025.
//

#include "Wizard.h"

    Wizard::Wizard(const std::string &name, int healthPoints, int maxHealthPoints)
        : Entity(name, healthPoints, maxHealthPoints) {
        quickSpells.push_back("Quick Firebolt");
        quickSpells.push_back("Quick Electric Shock");
        quickSpells.push_back("Quick Ice Spike");
    }



    void Wizard::printMana() {
        std::cout<<"         Mana: "<<manaStatus.getMana()<<'/'<<manaStatus.getTotalMana();
        for (int i = 0; i < manaStatus.getMana(); i++) {
            std::cout<<'|';
        }
        for (int i = 0; i < manaStatus.getTotalMana() - manaStatus.getMana(); i++) {
            std::cout<<'.';
        }
        std::cout<<'\n';
    }

    void Wizard::printAscensionStatus() {
        std::cout<<"    Ascension: "<<ascension.getProgress()<<'/'<<ascension.getThreshHold()<<' ';
        for (int i = 0; i < ascension.getProgress(); i++) {
            std::cout<<'|';
        }
        for (int i = 0; i < ascension.getThreshHold() - ascension.getProgress(); i++) {
            std::cout<<'.';
        }
        std::cout<<'\n';
    }

    void Wizard::checkAscension() {
        if (ascension.getProgress() == ascension.getThreshHold() && !ascension.getActive()) {
            ascension.activate();
            std::cout<<getName()<<" has ascended!\n";
        }
    }

    void Wizard::takeDamage(const Attack &attack) {

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

void Wizard::performAction(Entity& enemy) {
        int playerChoice;
        std::cout << "1. Magic Missile\n2. Blunt Staff\n3. Lightning Bolt\n4. Pillar of Fire\n5. Quick Spell\n";
        std::cout<<">>";
        std::cin >> playerChoice;

        switch (playerChoice) {
            case 1: enemy.takeDamage(this->magicMissile()); break;
            case 2: enemy.takeDamage(this->bluntStaff()); break;
            case 3: enemy.takeDamage(this->lightningBolt()); break;
            case 4: enemy.takeDamage(this->pillarOfFire()); break;
            case 5: enemy.takeDamage(this->quickSpell()); break;
            default: std::cout << this->getName() << " is concentrating on other matters\n"; break;
        }
        this->checkAscension();
    }

void Wizard::performEnemyAction(Entity &player) {

        int enemyChoice = rng.getInt(1,5);

        switch (enemyChoice) {
            case 1: player.takeDamage(this->magicMissile()); break;
            case 2: player.takeDamage(this->bluntStaff()); break;
            case 3: player.takeDamage(this->lightningBolt()); break;
            case 4: player.takeDamage(this->pillarOfFire()); break;
            case 5: player.takeDamage(this->quickSpell()); break;
            default: std::cout << this->getName() << " is concentrating on other matters\n"; break;
        }
        this->checkAscension();
}


    // ABILITIES ---------------------------------------------->

    Attack Wizard::qFireBolt() {

        Attack attack(damageType::Fire, 1);
        StatusEffect effect(statusEffectType::Burning, 1, 1);
        std::cout<<getName()<<" fired Quick Fire Bolt!\n";

        attack.setEffect(effect);
        return attack;
    }

    Attack Wizard::qElectricShock() {

        Attack attack(damageType::Lightning, 1);
        StatusEffect effect(statusEffectType::Electrified, 1, 1);
        std::cout<<getName()<<" fired Quick Electric shock!\n";

        attack.setEffect(effect);
        return attack;
    }

    Attack Wizard::qIceSpike() {

        Attack attack(damageType::Frost, 1);
        std::cout<<getName()<<" fired Quick Ice Spike!\n";

        return attack;
    }


    Attack Wizard::quickSpell() {

        Attack defaultAtk(damageType::Normal, 0);
        defaultAtk.nullifiyAttack();

            switch (quickSpells.size() - 1) {
                case 0:
                    quickSpells.pop_back();
                    return qFireBolt();
                case 1:
                    quickSpells.pop_back();
                    return qElectricShock();
                case 2:
                    quickSpells.pop_back();
                    return qIceSpike();
                default:
                    std::cout<<"No more quickspells left\n";
                    return defaultAtk;
            }

        }

    Attack Wizard::magicMissile() {

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

    Attack Wizard::bluntStaff() {
        // damage ability for a last resort when out of mana
        // if mana is 0, it deals double damage
        std::cout<<getName()<<" used Blunt Staff\n";
        Attack attack(damageType::Normal, 1);

        if (manaStatus.getMana() == 0) {
            attack.increaseDamage(1);
        }

        return attack;
    }

    Attack Wizard::lightningBolt() {

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

    Attack Wizard::pillarOfFire() {
        Attack attack(damageType::Fire, 2);
        StatusEffect effect = {statusEffectType::Burning, 2, 1};

        if (manaStatus.getMana() < 5) {
            attack.nullifiyAttack();
            std::cout<<getName()<<" tried to cast Pillar of Fire, but is out of mana!\n";
            return attack;
        }
        attack.setEffect(effect);

        manaStatus.regenMana(-5);
        ascension.increaseProgress(5);

        if (ascension.getActive() == true) {
            attack.increaseDamage(1);
            std::cout<<getName()<<" used Ascended Pillar of Fire!\n";
            return attack;
        }

        std::cout<<getName()<<" used Pillar of Fire!\n";
        std::cout<<"Enemy is burning!\n";
        return attack;
    }

    Wizard::~Wizard() = default;

std::ostream& operator<<(std::ostream& os, const Wizard& w) {

    os << static_cast<const Entity&>(w);
    os << w.ascension << w.manaStatus<<"\n";

    return os;
}