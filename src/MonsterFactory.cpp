#include "MonsterFactory.h"

Monster* MonsterFactory::spawnMonster(int difficultyModifier) {
    if (difficultyModifier <= 3) {
        return new Goblin("Goblin Ratacit", 30 + difficultyModifier * 2, 45, 5 + difficultyModifier);
    } 
    else if (difficultyModifier <= 15) {
        return new Goblin("Goblin Furios", 60 + difficultyModifier * 4, 100, 12 + difficultyModifier);
    } 
    else {
        return new Dragon("Dragon Stravechi", 150 + difficultyModifier * 10, 500, 25 + difficultyModifier);
    }
}