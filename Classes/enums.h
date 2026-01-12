//
// Created by bujor on 11/18/2025.
//


#ifndef ENUMS_H
#define ENUMS_H


enum class damageType {
    Normal, Slashing, Piercing, Magic, Blood, Holy, Fire, Lightning, Frost
};

enum class statusEffectType {
    None, Electrified, Bleeding, Poisoned, Burning, Wet
};

enum class weapons {
    None, Claymore, Hammer, Axe
};

enum class EntityType {
    Knight = 1,
    Vampire,
    Wizard,
    Blacksmith,
    Viking,
    Archer
};

//---------------->

#endif // ENUMS_H
