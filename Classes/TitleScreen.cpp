//
// Created by bujor on 11/18/2025.
//

#include "TitleScreen.h"

#include<iostream>


    void TitleScreen::printASCII() const{
        std::cout<<"      [\n";
        std::cout<<"<>xxxx[{::::::::::::::::::::::::> \n";
        std::cout<<"      [ \n";

        std::cout<<"           GAME TITLE\n";

        std::cout<<"                         [\n";
        std::cout<<"<::::::::::::::::::::::::[{xxxx<>\n";
        std::cout<<"                         [\n";
    }

    void  TitleScreen::printMenu() const{
        std::cout<<"\n";
        std::cout<<"[1] Start Game\n";
        std::cout<<"[2] About\n";
        std::cout<<"[3] Exit\n";
        std::cout<<">>";
    }

    void  TitleScreen::printAbout() const {
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

