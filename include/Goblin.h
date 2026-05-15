#ifndef GOBLIN_H
#define GOBLIN_H

#include "Monster.h"

class Goblin : public Monster {
public:
    Goblin(const std::string& n, int hp, int g, int dmg);
    void battleCry() const override;
};

#endif
