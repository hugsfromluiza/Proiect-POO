#ifndef GOBLIN_H
#define GOBLIN_H

#include "Monster.h"

class Goblin : public Monster {
public:
    Goblin(std::string n, int hp, int g, int dmg);
    void battleCry() const override;
};

#endif
