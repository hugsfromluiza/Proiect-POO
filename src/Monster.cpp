#include "Monster.h"

Monster::Monster(std::string n, int hp, int g, int dmg) : Entity(n, hp, g), damageOutput(dmg) {}

void Monster::takeDamage(int amount) {
    hp -= amount;
    if (hp < 0) hp = 0;
}

int Monster::attack() const { return damageOutput; }

