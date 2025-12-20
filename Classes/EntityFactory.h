//
// Created by bujor on 12/20/2025.
//

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <memory>
#include <string>
#include "Entity.h"


class EntityFactory {
public:
    static std::unique_ptr<Entity> createEntity(
        EntityType type,
        const std::string& name
    );
};



#endif //ENTITYFACTORY_H
