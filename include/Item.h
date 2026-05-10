#ifndef ITEM_H
#define ITEM_H
#include <string>

class Item {
protected:
    std::string name;
    int price;
public:
    Item();
    Item(std::string n, int prc);
    virtual ~Item();

Item::Item() : name("Unknown"), price(0) {}
Item::Item(std::string n, int prc) : name(n), price(prc) {}
Item::~Item() {}

std::string Item::getName() const { return name; }
int Item::getPrice() const { return price; }


    std::string getName() const;
    int getPrice() const;

    virtual void displayInfo() const = 0; // Clasa abstracta
};

#endif
