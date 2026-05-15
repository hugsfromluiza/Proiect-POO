#include "Player.h"
#include "GameException.h"
#include "Entity.h"
#include <iostream>

Player::Player() : Entity(), level(1) {}

Player::Player(const std::string& n, int hp, int g, int lvl) : Entity(n, hp, g), level(lvl) {}

Player::Player(const Player& other)
    : Entity(other), level(other.level), weapons(other.weapons), potions(other.potions) {}

Player& Player::operator=(const Player& other) {
    if (this != &other) {
        Entity::operator=(other);
        level = other.level;
        weapons = other.weapons;
        potions = other.potions;
    }
    return *this;
}

Player::~Player() {}

void Player::takeDamage(int amount) {
    hp -= amount;
    if (hp < 0) {
        hp = 0;
    }
}

int Player::getLevel() const {
    return level;
}

void Player::levelUp() {
    level++;
    hp += 20; // Bonus de vindecare la level up
    std::cout << "\n>>> NIVEL NOU DEBLOCAT! Ai ajuns la nivelul " << level << "!\n";
}

void Player::spendGold(int amount) {
    if (gold < amount) {
        throw LogicException("Aur insuficient pentru a finaliza tranzactia!");
    }
    gold -= amount;
}
void Player::addGold(int amount) {
    gold += amount;
}

Inventory<Weapon>& Player::getWeapons() {
    return weapons;
}

Inventory<Potion>& Player::getPotions() {
    return potions;
}
