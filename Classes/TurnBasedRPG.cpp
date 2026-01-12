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

#include "Archer.h"
#include "GameExceptions.h"
#include "Blacksmith.h"
#include "RNG.h"
#include "Viking.h"
#include "EntityFactory.h"

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
        player1->displayUniqueStats();
        std::cout<<"\n";

        player2->printHealthBar();
        player2->displayUniqueStats();

        std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
    }


void TurnBasedRPG::playerActionImproved() {

    player1->performAction(*player2);
    player1->takeEffectDamage();
}

void TurnBasedRPG::enemyActionImproved() {

    player2->performEnemyAction(*player1);
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
    std::string playerName;
    int classChoice;

    artificialDelay();
    std::cout << "Who are you?\n>> ";
    std::cin >> playerName;

    std::cout <<
        "Choose your class:\n"
        "1. Knight\n"
        "2. Vampire\n"
        "3. Wizard\n"
        "4. Blacksmith\n"
        "5. Viking\n"
        "6. Archer\n>>";

    std::cin >> classChoice;

    try {
        player1 = EntityFactory::createEntity(
            static_cast<EntityType>(classChoice),
            playerName
        );
    } catch (const InvalidClassException& e) {
        std::cout << e.what() << "\n";
        player1 = nullptr;
        return;
    }

    std::cout << "You are playing as " << player1->getName() << "\n";

    player2 = EntityFactory::createEntity(EntityType::Wizard, "Maegistus");
}


    TurnBasedRPG::TurnBasedRPG() = default;

    void TurnBasedRPG::runGame() {
        setupGame();

        if (!player1) {
            return;
        }

        bool gameOver = false;
        while (!gameOver) {
            displayStats();

            if (playerTurn == 0) {
                //playerAction();
                playerActionImproved();
            } else {
                artificialDelay();
                //enemyAction();
                enemyActionImproved();
            }

            gameOver = checkGameOver();

            std::cout<<"\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";

            playerTurn = 1 - playerTurn;

        }

    }


