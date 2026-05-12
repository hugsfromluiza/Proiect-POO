#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <algorithm>

template <typename T>
class Inventory {
private:
    std::vector<T> items;
public:
    Inventory();
    void addItem(const T& item);
    bool hasItems() const;
    void display() const;
    T getItem(int index) const;
    void removeItem(int index);
    int getSize() const;
    void sortInventory(); // Folosește lambda function
};

#endif
