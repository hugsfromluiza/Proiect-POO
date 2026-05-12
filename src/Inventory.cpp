#include "Inventory.h"
#include "Weapon.h"
#include "Potion.h"
#include <iostream>

template <typename T>
Inventory<T>::Inventory() {}

template <typename T>
void Inventory<T>::addItem(const T& item) { items.push_back(item); }

template <typename T>
bool Inventory<T>::hasItems() const { return !items.empty(); }

template <typename T>
void Inventory<T>::display() const {
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << i + 1 << ". ";
        items[i].displayInfo(); // Polimorfism
    }
}

template <typename T>
T Inventory<T>::getItem(int index) const { return items[index]; }

template <typename T>
void Inventory<T>::removeItem(int index) {
    items.erase(items.begin() + index);
}

template <typename T>
int Inventory<T>::getSize() const { return items.size(); }

template <>
void Inventory<Weapon>::sortInventory() {
    std::sort(items.begin(), items.end(), [](const Weapon& a, const Weapon& b) {
        return a.getDamage() > b.getDamage();
    });
}

template <>
void Inventory<Potion>::sortInventory() {
    std::sort(items.begin(), items.end(), [](const Potion& a, const Potion& b) {
        return a.getHealAmount() > b.getHealAmount();
    });
}

template class Inventory<Weapon>;
template class Inventory<Potion>;
