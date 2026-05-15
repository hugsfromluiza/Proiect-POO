#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Inventory.h"
#include "Weapon.h"
#include "Potion.h"

class Player : public Entity {
private:
    int level;
    Inventory<Weapon> weapons;
    Inventory<Potion> potions;

public:
    Player();
    Player(const std::string& n, int hp, int g, int lvl);
    Player(const Player& other);
    Player& operator=(const Player& other);
    ~Player() override;

    void takeDamage(int amount) override;

    int getLevel() const;
    void levelUp();
    void spendGold(int amount);
    void addGold(int amount);

    Inventory<Weapon>& getWeapons();
    Inventory<Potion>& getPotions();
};

#endif
