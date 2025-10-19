#ifdef SFML_AVAILABLE
#include "GUI.h"
#include <iostream>
#include <exception>

int main() {
    try {
        GUI gui;
        gui.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred!" << std::endl;
        return 1;
    }
    
    return 0;
}
#else
#include <iostream>
int main() {
    std::cout << "SFML not available. Please use the console version (main.cpp)" << std::endl;
    return 1;
}
#endif