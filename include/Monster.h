#ifndef MONSTER_H
#define MONSTER_H

#include "Entity.h"

class Monster : public Entity {
protected:
    int damageOutput;
public:
    Monster(std::string n, int hp, int g, int dmg);
    void takeDamage(int amount) override;
    virtual int attack() const;
    virtual void battleCry() const = 0;
};

class Goblin : public Monster {
public:
    Goblin(std::string n, int hp, int g, int dmg);
    void battleCry() const override;
};

class Dragon : public Monster {
public:
    Dragon(std::string n, int hp, int g, int dmg);
    void battleCry() const override;
    void fireBreath() const;
};

#endif
