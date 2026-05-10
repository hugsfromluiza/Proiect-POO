#include "Entity.h"

Entity::Entity() : name("Necunoscut"), hp(100), gold(0) {}

Entity::Entity(std::string n, int hp, int g) : name(n), hp(hp), gold(g) {}

Entity::Entity(const Entity& other) : name(other.name), hp(other.hp), gold(other.gold) {}

Entity& Entity::operator=(const Entity& other) {
    if (this != &other) {
        name = other.name;
        hp = other.hp;
        gold = other.gold;
    }
    return *this;
}

Entity& Entity::operator+=(int goldAmount) {
    this->gold += goldAmount;
    return *this;
}

Entity::~Entity() {}

std::string Entity::getName() const {
    return name;
}

int Entity::getHp() const {
    return hp;
}

int Entity::getGold() const {
    return gold;
}

bool Entity::isAlive() const {
    return hp > 0;
}

void Entity::heal(int amount) {
    hp += amount;
}

bool operator==(const Entity& a, const Entity& b) {
    return (a.getName() == b.getName()) && (a.getHp() == b.getHp());
}

std::ostream& operator<<(std::ostream& os, const Entity& e) {
    os << "[" << e.name << "] -> HP: " << e.hp << " | Aur: " << e.gold;
    return os;
}

std::istream& operator>>(std::istream& is, Entity& e) {
    std::cout << "Introdu Nume, HP si Aur: ";
    is >> e.name >> e.hp >> e.gold;
    return is;
}

