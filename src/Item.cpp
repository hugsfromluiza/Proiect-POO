#include "Item.h"

Item::Item() : name("Unknown"), price(0) {}
Item::Item(std::string n, int prc) : name(n), price(prc) {}
Item::~Item() {}

std::string Item::getName() const { return name; }
int Item::getPrice() const { return price; }
