#include "Monster.h"

Monster::Monster(std::string n, int hp, int g, int dmg) : Entity(n, hp, g), damageOutput(dmg) {}

void Monster::takeDamage(int amount) {
    hp -= amount;
    if (hp < 0) hp = 0;
}

int Monster::attack() const { return damageOutput; }

Goblin::Goblin(std::string n, int hp, int g, int dmg) : Monster(n, hp, g, dmg) {}
void Goblin::battleCry() const { std::cout << "Goblinul urla: Grahhh!\n"; }

Dragon::Dragon(std::string n, int hp, int g, int dmg) : Monster(n, hp, g, dmg) {}
void Dragon::battleCry() const { std::cout << "Dragonul rage: ROAAAAR!\n"; }
void Dragon::fireBreath() const { std::cout << "Dragonul scuipa foc!\n"; }
