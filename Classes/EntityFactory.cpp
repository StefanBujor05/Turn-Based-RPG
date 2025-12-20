//
// Created by bujor on 12/20/2025.
//

#include "EntityFactory.h"
#include "Knight.h"
#include "Vampire.h"
#include "Wizard.h"
#include "Blacksmith.h"
#include "Viking.h"
#include "GameExceptions.h"
#include "enums.h"

std::unique_ptr<Entity> EntityFactory::createEntity(
    EntityType type,
    const std::string& name
) {
    switch (type) {
        case EntityType::Knight:
            return std::make_unique<Knight>(name, 15, 15);
        case EntityType::Vampire:
            return std::make_unique<Vampire>(name, 11, 11);
        case EntityType::Wizard:
            return std::make_unique<Wizard>(name, 12, 12);
        case EntityType::Blacksmith:
            return std::make_unique<Blacksmith>(name, 13, 13, weapons::None, 0, 0);
        case EntityType::Viking:
            return std::make_unique<Viking>(name, 15, 15, 0, 7);
        default:
            throw InvalidClassException("Invalid entity type.");
    }
}
