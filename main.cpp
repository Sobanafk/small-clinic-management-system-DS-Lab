#include "MenuSystem.h"
#include <iostream>
#include <exception>

int main() {
    try {
        MenuSystem menuSystem;
        menuSystem.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred!" << std::endl;
        return 1;
    }
    
    return 0;
}