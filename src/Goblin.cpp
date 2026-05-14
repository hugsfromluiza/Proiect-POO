#include "../include/Goblin.h"

Goblin::Goblin(std::string n, int hp, int g, int dmg) : Monster(n, hp, g, dmg) {}

void Goblin::battleCry() const { std::cout << "Goblinul urla: Grahhh!\n"; }