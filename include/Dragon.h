#ifndef DRAGON_H
#define DRAGON_H

#include "Monster.h"

class Dragon : public Monster {
public:
    Dragon(std::string n, int hp, int g, int dmg);
    void battleCry() const override;
    void fireBreath() const;
};

#endif
