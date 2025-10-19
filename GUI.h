#ifndef GUI_H
#define GUI_H

#ifdef SFML_AVAILABLE
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Clinic.h"
#include <vector>
#include <string>

class GUI {
private:
    sf::RenderWindow window;
    Clinic* clinic;
    
    // Fonts and colors
    sf::Font font;
    sf::Color backgroundColor;
    sf::Color buttonColor;
    sf::Color textColor;
    sf::Color highlightColor;
    
    // UI Elements
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;
    std::vector<sf::Text> labels;
    std::vector<sf::RectangleShape> inputBoxes;
    std::vector<sf::Text> inputTexts;
    
    // Current state
    int currentScreen;
    int selectedButton;
    std::string currentInput;
    int currentInputBox;
    
    // Screen dimensions
    static const int WINDOW_WIDTH = 1200;
    static const int WINDOW_HEIGHT = 800;
    static const int BUTTON_WIDTH = 200;
    static const int BUTTON_HEIGHT = 50;
    static const int MARGIN = 20;
    
    // Screen constants
    enum Screen {
        MAIN_MENU = 0,
        PATIENT_MENU = 1,
        DOCTOR_MENU = 2,
        APPOINTMENT_MENU = 3,
        PATIENT_LIST = 4,
        DOCTOR_LIST = 5,
        APPOINTMENT_LIST = 6,
        ADD_PATIENT = 7,
        ADD_DOCTOR = 8,
        BOOK_APPOINTMENT = 9
    };

public:
    // Constructor and Destructor
    GUI();
    ~GUI();
    
    // Main functions
    bool initialize();
    void run();
    void cleanup();
    
    // Event handling
    void handleEvents();
    void handleMouseClick(sf::Vector2f mousePos);
    void handleTextInput(sf::Uint32 unicode);
    void handleKeyPress(sf::Keyboard::Key key);
    
    // Rendering
    void render();
    void renderMainMenu();
    void renderPatientMenu();
    void renderDoctorMenu();
    void renderAppointmentMenu();
    void renderPatientList();
    void renderDoctorList();
    void renderAppointmentList();
    void renderAddPatient();
    void renderAddDoctor();
    void renderBookAppointment();
    
    // UI Creation
    void createButton(const std::string& text, float x, float y, float width = BUTTON_WIDTH, float height = BUTTON_HEIGHT);
    void createLabel(const std::string& text, float x, float y, int size = 24);
    void createInputBox(float x, float y, float width = 300, float height = 30);
    void clearUI();
    
    // Utility functions
    bool loadFont();
    void setColors();
    void updateInputText();
    void drawText(const std::string& text, float x, float y, int size = 18, sf::Color color = sf::Color::Black);
    void drawCenteredText(const std::string& text, float y, int size = 24, sf::Color color = sf::Color::Black);
    void drawRectangle(float x, float y, float width, float height, sf::Color fillColor, sf::Color outlineColor = sf::Color::Black, float outlineThickness = 1.0f);
    
    // Data display
    void displayPatients();
    void displayDoctors();
    void displayAppointments();
    
    // Input handling
    void processAddPatient();
    void processAddDoctor();
    void processBookAppointment();
    
    // Getters
    bool isRunning() const;
};

#endif // SFML_AVAILABLE

#endif