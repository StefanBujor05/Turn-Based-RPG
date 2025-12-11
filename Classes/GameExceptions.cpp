//
// Created by bujor on 12/11/2025.
//

#include "GameExceptions.h"


// base exception class

GameExceptions::GameExceptions(const std::string& message ): msg_(message) {}

const char* GameExceptions::what() const noexcept {
    return msg_.c_str();
}


InvalidAbilityException::InvalidAbilityException(const std::string& message)
    :GameExceptions("Invalid ability usage error: " + message){}

InvalidClassException::InvalidClassException(const std::string& message)
    : GameExceptions("Invalid class: " + message){}

InvalidMenuException::InvalidMenuException(const std::string& message)
    : GameExceptions("Invalid menu choice: " + message){}