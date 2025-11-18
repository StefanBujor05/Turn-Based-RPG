/*
 * Bujor Stefan
 * Proiect POO - Turn-Based RPG (nume temporar)
*/
#include<iostream>
#include<random>
#include<ctime>
#include <memory>
#include<thread>
#include<chrono>
#include <functional>

#include "Classes/Entity.h"
#include "Classes/Knight.h"
#include "Classes/Vampire.h"
#include "Classes/Wizard.h"
#include "Classes/RNG.h"
#include "Classes/AcademicMagic.h"
#include "Classes/Attack.h"
#include "Classes/Mana.h"
#include "Classes/enums.h"
#include "Classes/Stance.h"
#include "Classes/StatusEffect.h"
#include "Classes/TitleScreen.h"
#include "Classes/TurnBasedRPG.h"

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