#include "GameEngine.h"
#include <iostream>
int main() {
    try {
        // Design Pattern Singleton
        GameEngine::getInstance().start();
         }
    catch (const std::exception& e) {
        // Upcast catch
        std::cerr << "Eroare critica in sistem: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
