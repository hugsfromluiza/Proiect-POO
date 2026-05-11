#ifndef WEAPON_H
#define WEAPON_H
#include "Item.h"

class Weapon : public Item {
private:
    int damage;
public:
    Weapon();
    Weapon(std::string n, int prc, int dmg);
    int getDamage() const;
    void displayInfo() const override;
};
#endif
