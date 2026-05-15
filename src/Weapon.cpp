#include "Weapon.h"
#include <iostream>

Weapon::Weapon() : Item(), damage(0) {}
Weapon::Weapon(const std::string& n, int prc, int dmg) : Item(n, prc), damage(dmg) {}
int Weapon::getDamage() const { return damage; }
void Weapon::displayInfo() const { std::cout << name << " (Dmg: " << damage << " | Pret: " << price << ")\n"; }
