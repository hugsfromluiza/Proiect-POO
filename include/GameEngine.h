#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Player.h"
#include "Monster.h"
#include <map>
#include <vector>

class GameEngine {
private:
    Player* currentPlayer;
    std::string currentLocation;
    bool isGameWon;
    struct PlayerData {
        int level;
        int hp;
        int gold;
        std::vector<Weapon> weapons;
        std::vector<Potion> potions;
    };

    std::map<std::string, PlayerData> saveFiles;
    std::vector<Weapon> shopWeapons;
    std::vector<Potion> shopPotions;

    static int diceRollsCount;

    GameEngine();
    ~GameEngine();
    void initShop();

public:
    static GameEngine& getInstance();
    GameEngine(const GameEngine&) = delete;
    void operator=(const GameEngine&) = delete;

    static int rollDice();

    void start();
    void loadData();
    void saveData();
    void displayInventory();

    void showMenu();
    void travel();
    void shop();
    void combat();
    void handleSpecialMonster(Monster* m);
};

#endif
