//
// Created by bujor on 11/18/2025.
//

#include "TurnBasedRPG.h"
#include "Entity.h"
#include <iostream>
#include "Wizard.h"
#include "Knight.h"
#include "Vampire.h"
#include <chrono>
#include <thread>
#include <random>
#include <memory>
#include "GameExceptions.h"
#include "Blacksmith.h"
#include "RNG.h"
#include "Viking.h"

void artificialDelay() {
    std::chrono::milliseconds delay_duration(500);
    for (int i = 0; i < 3; i++) {
        std::this_thread::sleep_for(delay_duration);
        std::cout << '.';
    }
    std::this_thread::sleep_for(delay_duration);
}

    void TurnBasedRPG::displayStats() const {
        std::cout << "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
        player1->printHealthBar();
        if (auto* wizard = dynamic_cast<Wizard*>(player1.get())) {
            wizard->printMana();
            wizard->printAscensionStatus();
        }
        else if (const auto* blacksmith = dynamic_cast<Blacksmith*>(player1.get())) {
            blacksmith->printStats();
        }
        else if (const auto* viking = dynamic_cast<Viking*>(player1.get())) {
            viking->printRage();
        }

        std::cout<<"\n";

        player2->printHealthBar();
        if (auto* wizard = dynamic_cast<Wizard*>(player2.get())) {
            wizard->printMana();
            wizard->printAscensionStatus();
        }
        else if (const auto* blacksmith = dynamic_cast<Blacksmith*>(player2.get())) {
            blacksmith->printStats();
        }
        else if (const auto* viking = dynamic_cast<Viking*>(player2.get())) {
            viking->printRage();
        }
        std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
    }

    void TurnBasedRPG::playerAction() {
        int playerChoice;


        std::cout<<"Choose an attack "<< player1->getName()<<": \n";



        if (dynamic_cast<Knight*>(player1.get())) {
            std::cout << "1. Sword Slash\n2. Preparation Lunge\n3. Holy Vow\n4. Opportunity Strike \n";
        } else if (dynamic_cast<Vampire*>(player1.get())) {
            std::cout << "1. Fang Bite\n2. Blood Splatter\n3. Blood Transfusion\n4. Blood Sacrifice\n";
        } else if (dynamic_cast<Wizard*>(player1.get())) {
            std::cout << "1. Magic Missile\n2. Blunt Staff\n3. Lightning Bolt\n4. Pillar of Fire\n5. Quick Spell\n";
        } else if (dynamic_cast<Blacksmith*>(player1.get())) {
            std::cout << "1. Choose weapon\n2. Enchance weapon \n3. Enchance armour\n4. Weapon attack\n";
        } else if (dynamic_cast<Viking*>(player1.get())) {
            std::cout << "1. Ancestral Scream\n2. Axe Chop \n3. Spirit Sweep\n4. Healing Prayer\n";
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
        } else if (auto* blacksmith = dynamic_cast<Blacksmith*>(player1.get())) {
            switch (playerChoice) {
                case 1: blacksmith->chooseWeapon(); break;
                case 2: blacksmith->echanceWeapon(); break;
                case 3: blacksmith->enhanceArmour(); break;
                case 4: player2->takeDamage(blacksmith->weaponAttack()); break;
                default: std::cout << blacksmith->getName() << " patiently waits...\n"; break;
            }
        } else if (auto* viking = dynamic_cast<Viking*>(player1.get())) {
            switch (playerChoice) {
                case 1: viking->ancestralScream(); break;
                case 2: player2->takeDamage(viking->axeChop()); break;
                case 3: player2->takeDamage(viking->spiritSweep()); break;
                case 4: viking->healingPrayer(); break;
                default: std::cout << viking->getName() << " watches...\n"; break;
            }
            viking->checkRage();
        } else if (auto* wizard = dynamic_cast<Wizard*>(player1.get())) {
            switch (playerChoice) {
                case 1: player2->takeDamage(wizard->magicMissile()); break;
                case 2: player2->takeDamage(wizard->bluntStaff()); break;
                case 3: player2->takeDamage(wizard->lightningBolt()); break;
                case 4: player2->takeDamage(wizard->pillarOfFire()); break;
                case 5: player2->takeDamage(wizard->quickSpell()); break;
                default: std::cout << wizard->getName() << " is concentrating on other matters\n"; break;
            }
            wizard->checkAscension();

        }
        player1->takeEffectDamage();
    }

    void TurnBasedRPG::enemyAction() {
        int player2Choice;
        srand(time(nullptr));
        //player2Choice = rand()%4 + 1;
        player2Choice = rng.getInt(1, 4);

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
        } else if (auto* blacksmith = dynamic_cast<Blacksmith*>(player2.get())) {
            switch (player2Choice) {
                case 1: blacksmith->chooseWeapon(); break;
                case 2: blacksmith->echanceWeapon(); break;
                case 3: blacksmith->enhanceArmour(); break;
                case 4: player1->takeDamage(blacksmith->weaponAttack()); break;
                default: std::cout << blacksmith->getName() << " patiently waits...\n"; break;
            }
        } else if (auto* viking = dynamic_cast<Viking*>(player2.get())) {
            switch (player2Choice) {
                case 1: viking->ancestralScream(); break;
                case 2: player1->takeDamage(viking->axeChop()); break;
                case 3: player1->takeDamage(viking->spiritSweep()); break;
                case 4: viking->healingPrayer(); break;
                default: std::cout << viking->getName() << " watches...\n"; break;
            }
            viking->checkRage();
        } else if (auto* wizard = dynamic_cast<Wizard*>(player2.get())) {
            switch (player2Choice) {
                case 1: player1->takeDamage(wizard->magicMissile()); break;
                case 2: player1->takeDamage(wizard->bluntStaff()); break;
                case 3: player1->takeDamage(wizard->lightningBolt()); break;
                case 4: player1->takeDamage(wizard->pillarOfFire()); break;
                case 5: player1->takeDamage(wizard->quickSpell()); break;
                default: std::cout << wizard->getName() << " is concentrating on other matters\n"; break;
            }
            wizard->checkAscension();
        }
        player2->takeEffectDamage();
    }

    bool TurnBasedRPG::checkGameOver() const {
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

    void TurnBasedRPG::setupGame() {
        int classChoice;
        std::string playerName;

        artificialDelay();
        std::cout<<"Who are you? \n>>";
        std::cin>>playerName;
        //std::cout<<"\n";
        std::cout<<"And what is your class?: \n1. Knight \n2. Vampire \n3. Wizard \n4. Blacksmith \n5. Viking\n>> ";
        std::cin>>classChoice;
        std::cout<<"\n";

    try {
        if (classChoice < 1 || classChoice > 5) {
            throw InvalidClassException(" class does not exist.");
        }

        switch(classChoice) {
            case 1:
                player1 = std::make_unique<Knight>(playerName, 15, 15);
                break;
            case 2:
                player1 = std::make_unique<Vampire>(playerName, 11, 11);
                break;
            case 3:
                player1 = std::make_unique<Wizard>(playerName, 12, 12);
                break;
            case 4:
                player1 = std::make_unique<Blacksmith>(playerName, 13, 13, weapons::None, 0, 0);
                break;
            case 5:
                player1 = std::make_unique<Viking>(playerName, 15, 15, 0, 7);
                break;
            default:
                std::cout<<"Invalid choice. Exiting game.\n";
                player1 = nullptr;
                return;
        }
    }
    catch (InvalidClassException& e){
        std::cout<<e.what()<<"\n";
    }

        std::cout<<"You are playing as "<<player1->getName()<<"\n";

        player2 = std::make_unique<Wizard>("Maegistus", 12, 12);
    }



    TurnBasedRPG::TurnBasedRPG() = default;

    void TurnBasedRPG::runGame() {
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

            std::cout<<"\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";

            playerTurn = 1 - playerTurn;

        }

    }
