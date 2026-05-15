#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include <iostream>

class Entity {
protected:
    std::string name;
    int hp;
    int gold;

public:
    Entity();
    Entity(std::string n, int hp, int g);
    Entity(const Entity& other);
    Entity& operator=(const Entity& other);
    Entity& operator+=(int goldAmount);
    virtual ~Entity();

    virtual void takeDamage(int amount) = 0;
    const std::string& getName() const;
    int getHp() const;
    int getGold() const;
    bool isAlive() const;
    void heal(int amount);

    friend std::ostream& operator<<(std::ostream& os, const Entity& e);
    friend std::istream& operator>>(std::istream& is, Entity& e);
};

bool operator==(const Entity& a, const Entity& b);

#endif