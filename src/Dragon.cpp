#include "Dragon.h"

Dragon::Dragon(const std::string& n, int hp, int g, int dmg) : Monster(n, hp, g, dmg) {}
void Dragon::battleCry() const { std::cout << "Dragonul rage: ROAAAAR!\n"; }
void Dragon::fireBreath() const { std::cout << "Dragonul scuipa foc!\n"; }