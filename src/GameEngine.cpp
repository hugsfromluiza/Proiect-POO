#include "GameEngine.h"
#include "MonsterFactory.h"
#include "GameException.h"
#include <iostream>
#include <fstream>
#include <random>

int GameEngine::diceRollsCount = 0;

// Constructor privat (Design Pattern Singleton)
GameEngine::GameEngine() : currentPlayer(nullptr), currentLocation("Town Square"), isGameWon(false) {
    initShop();
}

// Destructor pt memory leaks
GameEngine::~GameEngine() {
    delete currentPlayer;
}

GameEngine& GameEngine::getInstance() {
    static GameEngine instance;
    return instance;
}

int GameEngine::rollDice() {
    diceRollsCount++;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 20);
    return dis(gen);
}

void GameEngine::initShop() {
    shopWeapons.push_back(Weapon("Pumnal de Boier", 20, 20));
    shopWeapons.push_back(Weapon("Sabie Scurta", 30, 30));
    shopWeapons.push_back(Weapon("Topor de Batalie", 50, 45));
    shopWeapons.push_back(Weapon("Buzdugan Greu", 70, 60));
    shopWeapons.push_back(Weapon("Sabie Lunga", 90, 80));
    shopWeapons.push_back(Weapon("Ciocan de Lupta", 150, 105));
    shopWeapons.push_back(Weapon("Sabie de Argint", 200, 135));
    shopWeapons.push_back(Weapon("Topor Dublu", 350, 170));
    shopWeapons.push_back(Weapon("Sabie de Titan", 500, 210));
    shopWeapons.push_back(Weapon("Sabia Campionului", 700, 260));

    shopPotions.push_back(Potion("Potiune XS", 10, 25));
    shopPotions.push_back(Potion("Potiune S", 25, 50));
    shopPotions.push_back(Potion("Potiune M", 50, 80));
    shopPotions.push_back(Potion("Potiune L", 90, 130));
    shopPotions.push_back(Potion("Potiune XL", 150, 200));
    shopPotions.push_back(Potion("Potiune XXL", 250, 300));
    shopPotions.push_back(Potion("Potiune de Zeu", 400, 450));
    shopPotions.push_back(Potion("Potiune Maxima", 600, 600));
    shopPotions.push_back(Potion("Elixir de Vindecare", 900, 850));
    shopPotions.push_back(Potion("Potiunea Eroului", 1300, 1200));
}

void GameEngine::loadData() {
    std::ifstream file("saves.txt");
    if (!file) {
        std::cout << "[INFO] Nu s-a gasit fisierul de salvari. Se va crea unul nou.\n";
        return;
    }

    std::string token;
    while (file >> token) {
        if (token == "NAME") {
            std::string name;
            file >> name;
            PlayerData pd;
            file >> pd.level >> pd.hp >> pd.gold;

            int wCount = 0;
            file >> wCount;
            for(int i = 0; i < wCount; ++i) {
                std::string wName;
                std::getline(file >> std::ws, wName);
                int wPrice = 0, wDmg = 0;
                file >> wPrice >> wDmg;
                pd.weapons.push_back(Weapon(wName, wPrice, wDmg));
            }

            int pCount = 0;
            file >> pCount;
            for(int i = 0; i < pCount; ++i) {
                std::string pName;
                std::getline(file >> std::ws, pName);
                int pPrice = 0, pHeal = 0;
                file >> pPrice >> pHeal;
                pd.potions.push_back(Potion(pName, pPrice, pHeal));
            }
            saveFiles[name] = pd;
        }
    }
    file.close();
}

void GameEngine::saveData() {
    if (currentPlayer != nullptr) {
        if (currentPlayer->isAlive()) {
            PlayerData pd;
            pd.level = currentPlayer->getLevel();
            pd.hp = currentPlayer->getHp();
            pd.gold = currentPlayer->getGold();

            for (int i = 0; i < currentPlayer->getWeapons().getSize(); ++i)
                pd.weapons.push_back(currentPlayer->getWeapons().getItem(i));

            for (int i = 0; i < currentPlayer->getPotions().getSize(); ++i)
                pd.potions.push_back(currentPlayer->getPotions().getItem(i));

            saveFiles[currentPlayer->getName()] = pd;
        } else
            saveFiles.erase(currentPlayer->getName());

    }

    std::ofstream file("saves.txt");
    for (const auto& pair : saveFiles) {
        file << "NAME\n" << pair.first << "\n";
        file << pair.second.level << " " << pair.second.hp << " " << pair.second.gold << "\n";
        file << pair.second.weapons.size() << "\n";
        for (const auto& w : pair.second.weapons)
            file << w.getName() << "\n" << w.getPrice() << " " << w.getDamage() << "\n";
        file << pair.second.potions.size() << "\n";
        for (const auto& p : pair.second.potions)
            file << p.getName() << "\n" << p.getPrice() << " " << p.getHealAmount() << "\n";
    }
    file.close();
}

void GameEngine::start() {
    loadData();

    std::string name;
    std::cout << "Introdu numele eroului tau : ";

    if (!(std::cin >> name)) {
        name = "ErouDeTest";
    }

    if (saveFiles.find(name) != saveFiles.end()) {
        PlayerData pd = saveFiles[name];
        std::cout << "\nBine ai revenit, " << name << "! Continui aventura de unde ai ramas.\n";

        currentPlayer = new Player(name, pd.hp, pd.gold, pd.level);

        for (const auto& w : pd.weapons) currentPlayer->getWeapons().addItem(w);
        for (const auto& p : pd.potions) currentPlayer->getPotions().addItem(p);

    } else {
        std::cout << "\nUn nou erou se naste in acest taram!\n";
        currentPlayer = new Player(name, 100, 50, 1);
        currentPlayer->getWeapons().addItem(Weapon("Pumnal de noob", 0, 10));
    }

    showMenu();
}

void GameEngine::showMenu() {
    char choice='Z';
    do {
        std::cout << "\n=== MENIUL PRINCIPAL ===\n";
        std::cout << "Locatie: " << currentLocation << "\n";
        std::cout << *currentPlayer << "\n";
        std::cout << "A. Calatoreste in alta zona\n";
        std::cout << "B. Viziteaza magazinul\n";
        std::cout << "C. Lupta!\n";
        std::cout << "D. Salveaza progresul si iesi\n";
        std::cout << "E. Afiseaza inventarul\n";
        std::cout << "Alegerea ta: ";

        if (!(std::cin >> choice)) {
            std::cout << "\n[Sistem] Jocul s-a oprit deoarece nu mai exista input.\n";
            break;
        }

        switch (toupper(choice))
        {
            case 'A': travel(); break;
            case 'B': shop(); break;
            case 'C': combat(); break;
            case 'E': displayInventory(); break;
            case 'D':
                saveData();
                std::cout << "Jocul a fost salvat complet! La revedere!\n";
                break;
            default:
                std::cout << "Alegere invalida. Incearca din nou!\n";
        }
    } while (toupper(choice) != 'D' && currentPlayer->isAlive() && !isGameWon);

    if (isGameWon) {
        std::cout << "\n*** Legenda ta a fost scrisa! Eroul tau se retrage in glorie. ***\n";
        saveFiles.erase(currentPlayer->getName());
        saveData();
    }
    else if (!currentPlayer->isAlive()) {
        std::cout << "\nAi pierit in lupta... Aventura ta se termina aici.\n";
        std::cout << "Eroul tau a fost sters din istoric (Salvare stearsa).\n";
        saveData();
    }
}

void GameEngine::displayInventory() {
    std::cout << "\n============================================\n";
    std::cout << " INVENTARUL LUI " << currentPlayer->getName() << "\n";
    std::cout << " Aur disponibil: " << currentPlayer->getGold() << "\n";
    std::cout << "--------------------------------------------\n";
    std::cout << "[ ARME ]\n";
    if (currentPlayer->getWeapons().hasItems()) {
        currentPlayer->getWeapons().display();
    } else
        std::cout << " - Nu ai nicio arma echipata.\n";

    std::cout << "\n[ POTIUNI ]\n";
    if (currentPlayer->getPotions().hasItems()) {
        currentPlayer->getPotions().display();
    } else
        std::cout << " - Nu ai nicio potiune.\n";

    std::cout << "============================================\n";
}

void GameEngine::travel() {
    std::cout << "\nIncotro vrei sa te indrepti?\n";
    std::cout << "1. Padurea Blestemata (Pericol scazut)\n";
    std::cout << "2. Temnita Abandonata (Pericol mediu)\n";
    std::cout << "3. Varful Dragonului (Pericol maxim)\n";
    std::cout << "Alegere: ";

    int c;
    if (!(std::cin >> c)) return;
    try {
        if (c < 1 || c > 3)
            throw LogicException("Destinatie inexistenta pe harta!");
        if (c == 1) currentLocation = "Padurea Blestemata";
        else if (c == 2) currentLocation = "Temnita Abandonata";
        else currentLocation = "Varful Dragonului";

    } catch (const GameException& e) {
        std::cout << "\n[Eroare Calatorie] " << e.what() << " Ai ramas pe loc.\n";
    }
}

void GameEngine::shop() {
    std::cout << "\n=== NEGUSTORUL AMBULANT === (Aurul tau: " << currentPlayer->getGold() << ")\n";
    std::cout << "Ce doresti sa examinezi?\n1. Arme\n2. Potiuni\n3. Inapoi\nAlegere: ";
    int cat;
    if (!(std::cin >> cat)) return;

    if (cat == 1) {
        std::cout << "\n--- ARME DISPONIBILE ---\n";
        for (size_t i = 0; i < shopWeapons.size(); ++i) {
            std::cout << i + 1 << ". ";
            shopWeapons[i].displayInfo();
        }
        std::cout << "Introdu numarul armei (0 pt a renunta): ";
        int choice;
        if (!(std::cin >> choice)) return;

        if (choice > 0 && choice <= (int)shopWeapons.size()) {
            try {
                currentPlayer->spendGold(shopWeapons[choice-1].getPrice());
                currentPlayer->getWeapons().addItem(shopWeapons[choice-1]);
                currentPlayer->getWeapons().sortInventory(); // Sortare cu functie lambda
                std::cout << "Ai cumparat cu succes: " << shopWeapons[choice-1].getName() << "\n";
            } catch (const GameException& e) {
                std::cout << "Negustorul rade de tine: " << e.what() << "\n";
            }
        }
    } else if (cat == 2) {
        std::cout << "\n--- POTIUNI DISPONIBILE ---\n";
        for (size_t i = 0; i < shopPotions.size(); ++i) {
            std::cout << i + 1 << ". ";
            shopPotions[i].displayInfo();
        }
        std::cout << "Introdu numarul potiunii (0 pt a renunta): ";
        int choice;
        if (!(std::cin >> choice)) return;

        if (choice > 0 && choice <= (int)shopPotions.size()) {
            try {
                currentPlayer->spendGold(shopPotions[choice-1].getPrice());
                currentPlayer->getPotions().addItem(shopPotions[choice-1]);
                currentPlayer->getPotions().sortInventory();
                std::cout << "Ai cumparat cu succes: " << shopPotions[choice-1].getName() << "\n";
            } catch (const GameException& e) {
                std::cout << "Negustorul rade de tine: " << e.what() << "\n";
            }
        }
    }
}

void GameEngine::handleSpecialMonster(Monster* m) {
    // Upcast
    m->battleCry();

    // Downcast
    const Dragon* dragon = dynamic_cast<Dragon*>(m);
    if (dragon != nullptr) {
        std::cout << "O creatura legendara se afla in fata ta!\n";
        dragon->fireBreath();
    }
}

void GameEngine::combat() {
    int difficultyModifier = currentPlayer->getLevel();
    if (currentLocation == "Varful Dragonului")
        difficultyModifier += 5;
    else if (currentLocation == "Temnita Abandonata")
        difficultyModifier += 2;
    Monster* enemy = MonsterFactory::spawnMonster(difficultyModifier);
    std::cout << "\nUn " << enemy->getName() << " iti blocheaza calea!\n";
    handleSpecialMonster(enemy);
    while (currentPlayer->isAlive()) {
        std::cout << "\n--- RANDUL TAU ---\nHP Jucator: " << currentPlayer->getHp() << " | HP Monstru: " << enemy->getHp() << "\n";
        std::cout << "1. Ataca cu o arma\n2. Foloseste o potiune\nAlege o actiune: ";
        int actiune=0;
        if (!(std::cin >> actiune)) break;
        try {
            if (actiune != 1 && actiune != 2) {
                throw LogicException("Actiune de lupta necunoscuta! Te-ai blocat de frica.");
            }
            if (actiune == 1) {
                if (!currentPlayer->getWeapons().hasItems()) {
                    std::cout << "Nu ai nicio arma! Lovesti cu pumnii (1 damage).\n";
                    enemy->takeDamage(1);
                } else {
                    std::cout << "Alege arma cu care vrei sa lovesti:\n";
                    currentPlayer->getWeapons().display();
                    int wChoice=0;
                    if (!(std::cin >> wChoice)) break;
                    if (wChoice <= 0 || wChoice > currentPlayer->getWeapons().getSize()) {
                        throw LogicException("Ai bajbait prin inventar si nu ai gasit arma dorita!");
                    }
                    Weapon w = currentPlayer->getWeapons().getItem(wChoice - 1);
                    int roll = rollDice();
                    std::cout << "\nAi dat un " << roll << " la zar! ";
                    if (roll >= 10 && roll < 13) {
                        std::cout << "Lovitura a prins in plin! Dai " << w.getDamage()/2 << " damage.\n";
                        enemy->takeDamage(w.getDamage()/2);
                    } else if (roll >= 13 && roll < 18) {
                        std::cout << "Lovitura a prins in plin! Dai " << 3*w.getDamage()/4 << " damage.\n";
                        enemy->takeDamage(3*w.getDamage()/4);
                    } else if (roll >= 18) {
                        std::cout << "Lovitura a prins in plin! Dai " << w.getDamage() << " damage.\n";
                        enemy->takeDamage(w.getDamage());
                    } else if (roll == 1) {
                        std::cout << "Esec critic! Te-ai impiedicat si arma ti-a alunecat din mana.\n";
                    } else {
                        std::cout << "Monstrul a fentat atacul tau!\n";
                    }
                }
            }
            else if (actiune == 2) {
                if (!currentPlayer->getPotions().hasItems()) {
                    std::cout << "Nu ai nicio potiune! Iti pierzi randul cautand in gol prin buzunare.\n";
                } else {
                    std::cout << "Alege potiunea pe care vrei sa o consumi:\n";
                    currentPlayer->getPotions().display();
                    int pChoice=0;
                    if (!(std::cin >> pChoice)) break;
                    if (pChoice <= 0 || pChoice > currentPlayer->getPotions().getSize()) {
                        throw LogicException("Ai intins mana dupa o sticluta care nu exista!");
                    }
                    Potion p = currentPlayer->getPotions().getItem(pChoice - 1);
                    int roll = rollDice();
                    if (roll >= 5) {
                        currentPlayer->heal(p.getHealAmount());
                        std::cout << "\nAi baut " << p.getName() << " si ti-ai refacut " << p.getHealAmount() << " HP!\n";
                        currentPlayer->getPotions().removeItem(pChoice - 1);
                    } else {
                        std::cout << "\nZar mic (" << roll << ")! Fiind grabit in mijlocul luptei, ai scapat sticluta din mana. Potiunea s-a irosit!\n";
                        currentPlayer->getPotions().removeItem(pChoice - 1);
                    }
                }
            }
        }
        catch (const GameException& e) {
            std::cout << "\n[Actiune Esuata] " << e.what() << " Ti-ai pierdut randul!\n";
        }
        if (!enemy->isAlive()) {
            break;
        }
        std::cout << "\n--- RANDUL INAMICULUI ---\n";
        int roll = rollDice();
        if (roll >= 12) {
            int dmgTaken = enemy->attack();
            std::cout << "Monstrul " << enemy->getName() << " te-a lovit puternic! Pierzi " << dmgTaken << " HP.\n";
            currentPlayer->takeDamage(dmgTaken);
        } else {
            std::cout << "Atacul monstrului a trecut pe langa tine!\n";
        }
    }

    if (currentPlayer->isAlive()) {
        std::cout << "\n VICTORIE! Ai infrant " << enemy->getName() << "\n";

        if (enemy->getName() == "Dragon Stravechi" && currentPlayer->getLevel() >= 20) {
            std::cout << "\n======================================================\n";
            std::cout << "FELICITARI! Ai ucis Lordul Dragonilor si ai salvat regatul!\n";
            std::cout << "Ai terminat jocul cu succes!\n";
            std::cout << "======================================================\n";
            isGameWon = true;
        } else {
            int loot = enemy->getGold();
            std::cout << "Ai adunat " << loot << " aur din ramasitele inamicului.\n";
            currentPlayer->addGold(loot);
            currentPlayer->levelUp();
        }
    }

    delete enemy;
}
