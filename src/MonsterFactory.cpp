#include "MonsterFactory.h"

Monster* MonsterFactory::spawnMonster(int difficultyModifier) {
    if (difficultyModifier <= 2) {
        return new Goblin("Goblin Ratacit", 30 + difficultyModifier * 5, 15, 5 + difficultyModifier);
    } 
    else if (difficultyModifier <= 5) {
        return new Goblin("Hobgoblin Furios", 60 + difficultyModifier * 5, 30, 12 + difficultyModifier);
    } 
    else {
        return new Dragon("Dragon Stravechi", 150 + difficultyModifier * 10, 200, 25 + difficultyModifier);
    }
}