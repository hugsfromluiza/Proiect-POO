#ifndef MONSTERFACTORY_H
#define MONSTERFACTORY_H

#include "Monster.h"

class MonsterFactory {
public:
    static Monster* spawnMonster(int difficultyModifier);
};

#endif
