#include "Potion.h"
#include <iostream>

Potion::Potion() : Item(), healAmount(0) {}
Potion::Potion(const std::string& n, int prc, int heal) : Item(n, prc), healAmount(heal) {}
int Potion::getHealAmount() const { return healAmount; }
void Potion::displayInfo() const { std::cout << name << " (Heal: " << healAmount << " | Pret: " << price << ")\n"; }
