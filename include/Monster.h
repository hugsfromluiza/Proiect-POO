#ifndef MONSTER_H
#define MONSTER_H

#include "Entity.h"

class Monster : public Entity {
protected:
    int damageOutput;
public:
    Monster(const std::string& n, int hp, int g, int dmg);
    void takeDamage(int amount) override;
    virtual int attack() const;
    virtual void battleCry() const = 0;
};

#endif
