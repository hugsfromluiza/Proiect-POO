#ifndef POTION_H
#define POTION_H

#include "Item.h"

class Potion : public Item {
private:
    int healAmount;
public:
    Potion();
    Potion(std::string n, int prc, int heal);
    int getHealAmount() const;
    void displayInfo() const override;
};
#endif
