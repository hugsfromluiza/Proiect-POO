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

    std::string getName() const;
    int getPrice() const;

    virtual void displayInfo() const = 0; // Clasa abstracta
};

#endif
