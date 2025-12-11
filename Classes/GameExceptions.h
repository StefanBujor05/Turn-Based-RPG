//
// Created by bujor on 12/11/2025.
//

#ifndef GAMEEXCEPTIONS_H
#define GAMEEXCEPTIONS_H

#include <exception>
#include <string>


class GameExceptions: public std::exception {

    std::string msg_;

public:
    explicit GameExceptions(const std::string& message );

    [[nodiscard]]const char* what() const noexcept override;

};

class InvalidAbilityException: public GameExceptions {
    public:
    explicit InvalidAbilityException(const std::string& message);
};

// game class (eg. Wizard etc.)
class InvalidClassException: public GameExceptions {
    public:
    explicit InvalidClassException(const std::string& message);
};

class InvalidMenuException: public GameExceptions {
    public:
    explicit InvalidMenuException(const std::string& message);
};



#endif //GAMEEXCEPTIONS_H
