#ifdef SFML_AVAILABLE

#include "GUI.h"
#include <iostream>
#include <sstream>

// Constructor
GUI::GUI() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Clinic Management System"), 
             clinic(nullptr), currentScreen(MAIN_MENU), selectedButton(-1), currentInputBox(-1) {
    clinic = new Clinic();
    setColors();
}

// Destructor
GUI::~GUI() {
    delete clinic;
}

// Initialize GUI
bool GUI::initialize() {
    if (!loadFont()) {
        std::cerr << "Failed to load font!" << std::endl;
        return false;
    }
    
    window.setFramerateLimit(60);
    return true;
}

// Main run loop
void GUI::run() {
    if (!initialize()) {
        return;
    }
    
    while (window.isOpen()) {
        handleEvents();
        render();
    }
    
    cleanup();
}

// Handle events
void GUI::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    handleMouseClick(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                }
                break;
            case sf::Event::TextEntered:
                handleTextInput(event.text.unicode);
                break;
            case sf::Event::KeyPressed:
                handleKeyPress(event.key.code);
                break;
        }
    }
}

// Handle mouse clicks
void GUI::handleMouseClick(sf::Vector2f mousePos) {
    // Check button clicks
    for (size_t i = 0; i < buttons.size(); i++) {
        if (buttons[i].getGlobalBounds().contains(mousePos)) {
            selectedButton = i;
            break;
        }
    }
    
    // Check input box clicks
    for (size_t i = 0; i < inputBoxes.size(); i++) {
        if (inputBoxes[i].getGlobalBounds().contains(mousePos)) {
            currentInputBox = i;
            currentInput = inputTexts[i].getString();
            break;
        }
    }
}

// Handle text input
void GUI::handleTextInput(sf::Uint32 unicode) {
    if (currentInputBox >= 0 && currentInputBox < inputTexts.size()) {
        if (unicode == 8) { // Backspace
            if (!currentInput.empty()) {
                currentInput.pop_back();
            }
        } else if (unicode >= 32 && unicode <= 126) { // Printable characters
            currentInput += static_cast<char>(unicode);
        }
        updateInputText();
    }
}

// Handle key presses
void GUI::handleKeyPress(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Escape:
            if (currentScreen == MAIN_MENU) {
                window.close();
            } else {
                currentScreen = MAIN_MENU;
                clearUI();
            }
            break;
        case sf::Keyboard::Return:
            if (currentInputBox >= 0) {
                processCurrentInput();
            }
            break;
        case sf::Keyboard::Tab:
            if (currentInputBox >= 0) {
                currentInputBox = (currentInputBox + 1) % inputBoxes.size();
                currentInput = inputTexts[currentInputBox].getString();
            }
            break;
    }
}

// Process current input based on screen
void GUI::processCurrentInput() {
    switch (currentScreen) {
        case ADD_PATIENT:
            processAddPatient();
            break;
        case ADD_DOCTOR:
            processAddDoctor();
            break;
        case BOOK_APPOINTMENT:
            processBookAppointment();
            break;
    }
}

// Render everything
void GUI::render() {
    window.clear(backgroundColor);
    
    switch (currentScreen) {
        case MAIN_MENU:
            renderMainMenu();
            break;
        case PATIENT_MENU:
            renderPatientMenu();
            break;
        case DOCTOR_MENU:
            renderDoctorMenu();
            break;
        case APPOINTMENT_MENU:
            renderAppointmentMenu();
            break;
        case PATIENT_LIST:
            renderPatientList();
            break;
        case DOCTOR_LIST:
            renderDoctorList();
            break;
        case APPOINTMENT_LIST:
            renderAppointmentList();
            break;
        case ADD_PATIENT:
            renderAddPatient();
            break;
        case ADD_DOCTOR:
            renderAddDoctor();
            break;
        case BOOK_APPOINTMENT:
            renderBookAppointment();
            break;
    }
    
    window.display();
}

// Render main menu
void GUI::renderMainMenu() {
    clearUI();
    
    drawCenteredText("Clinic Management System", 50, 36, sf::Color::Blue);
    
    createButton("Patient Management", WINDOW_WIDTH/2 - BUTTON_WIDTH/2, 150);
    createButton("Doctor Management", WINDOW_WIDTH/2 - BUTTON_WIDTH/2, 220);
    createButton("Appointment Management", WINDOW_WIDTH/2 - BUTTON_WIDTH/2, 290);
    createButton("View Statistics", WINDOW_WIDTH/2 - BUTTON_WIDTH/2, 360);
    createButton("Exit", WINDOW_WIDTH/2 - BUTTON_WIDTH/2, 430);
    
    // Handle button clicks
    if (selectedButton >= 0) {
        switch (selectedButton) {
            case 0: currentScreen = PATIENT_MENU; break;
            case 1: currentScreen = DOCTOR_MENU; break;
            case 2: currentScreen = APPOINTMENT_MENU; break;
            case 3: 
                clinic->displayStatistics();
                currentScreen = MAIN_MENU;
                break;
            case 4: window.close(); break;
        }
        selectedButton = -1;
    }
}

// Render patient menu
void GUI::renderPatientMenu() {
    clearUI();
    
    drawCenteredText("Patient Management", 50, 28, sf::Color::Blue);
    
    createButton("Add Patient", 50, 120);
    createButton("View All Patients", 300, 120);
    createButton("Search Patients", 550, 120);
    createButton("Back to Main Menu", 50, 200);
    
    if (selectedButton >= 0) {
        switch (selectedButton) {
            case 0: currentScreen = ADD_PATIENT; break;
            case 1: currentScreen = PATIENT_LIST; break;
            case 2: 
                // Search functionality would go here
                break;
            case 3: currentScreen = MAIN_MENU; break;
        }
        selectedButton = -1;
    }
}

// Render doctor menu
void GUI::renderDoctorMenu() {
    clearUI();
    
    drawCenteredText("Doctor Management", 50, 28, sf::Color::Blue);
    
    createButton("Add Doctor", 50, 120);
    createButton("View All Doctors", 300, 120);
    createButton("Search Doctors", 550, 120);
    createButton("Back to Main Menu", 50, 200);
    
    if (selectedButton >= 0) {
        switch (selectedButton) {
            case 0: currentScreen = ADD_DOCTOR; break;
            case 1: currentScreen = DOCTOR_LIST; break;
            case 2: 
                // Search functionality would go here
                break;
            case 3: currentScreen = MAIN_MENU; break;
        }
        selectedButton = -1;
    }
}

// Render appointment menu
void GUI::renderAppointmentMenu() {
    clearUI();
    
    drawCenteredText("Appointment Management", 50, 28, sf::Color::Blue);
    
    createButton("Book Appointment", 50, 120);
    createButton("View All Appointments", 300, 120);
    createButton("Search Appointments", 550, 120);
    createButton("Back to Main Menu", 50, 200);
    
    if (selectedButton >= 0) {
        switch (selectedButton) {
            case 0: currentScreen = BOOK_APPOINTMENT; break;
            case 1: currentScreen = APPOINTMENT_LIST; break;
            case 2: 
                // Search functionality would go here
                break;
            case 3: currentScreen = MAIN_MENU; break;
        }
        selectedButton = -1;
    }
}

// Render patient list
void GUI::renderPatientList() {
    clearUI();
    
    drawCenteredText("All Patients", 50, 28, sf::Color::Blue);
    createButton("Back", 50, 50);
    
    displayPatients();
    
    if (selectedButton >= 0) {
        currentScreen = PATIENT_MENU;
        selectedButton = -1;
    }
}

// Render doctor list
void GUI::renderDoctorList() {
    clearUI();
    
    drawCenteredText("All Doctors", 50, 28, sf::Color::Blue);
    createButton("Back", 50, 50);
    
    displayDoctors();
    
    if (selectedButton >= 0) {
        currentScreen = DOCTOR_MENU;
        selectedButton = -1;
    }
}

// Render appointment list
void GUI::renderAppointmentList() {
    clearUI();
    
    drawCenteredText("All Appointments", 50, 28, sf::Color::Blue);
    createButton("Back", 50, 50);
    
    displayAppointments();
    
    if (selectedButton >= 0) {
        currentScreen = APPOINTMENT_MENU;
        selectedButton = -1;
    }
}

// Render add patient form
void GUI::renderAddPatient() {
    clearUI();
    
    drawCenteredText("Add New Patient", 50, 28, sf::Color::Blue);
    
    createLabel("Name:", 50, 120);
    createInputBox(150, 120);
    
    createLabel("Age:", 50, 170);
    createInputBox(150, 170);
    
    createLabel("Disease:", 50, 220);
    createInputBox(150, 220);
    
    createLabel("Contact:", 50, 270);
    createInputBox(150, 270);
    
    createLabel("Address:", 50, 320);
    createInputBox(150, 320);
    
    createButton("Add Patient", 150, 400);
    createButton("Cancel", 400, 400);
    
    if (selectedButton >= 0) {
        if (selectedButton == 0) {
            processAddPatient();
        } else {
            currentScreen = PATIENT_MENU;
        }
        selectedButton = -1;
    }
}

// Render add doctor form
void GUI::renderAddDoctor() {
    clearUI();
    
    drawCenteredText("Add New Doctor", 50, 28, sf::Color::Blue);
    
    createLabel("Name:", 50, 120);
    createInputBox(150, 120);
    
    createLabel("Specialization:", 50, 170);
    createInputBox(150, 170);
    
    createLabel("Contact:", 50, 220);
    createInputBox(150, 220);
    
    createLabel("Schedule:", 50, 270);
    createInputBox(150, 270);
    
    createButton("Add Doctor", 150, 400);
    createButton("Cancel", 400, 400);
    
    if (selectedButton >= 0) {
        if (selectedButton == 0) {
            processAddDoctor();
        } else {
            currentScreen = DOCTOR_MENU;
        }
        selectedButton = -1;
    }
}

// Render book appointment form
void GUI::renderBookAppointment() {
    clearUI();
    
    drawCenteredText("Book Appointment", 50, 28, sf::Color::Blue);
    
    createLabel("Patient ID:", 50, 120);
    createInputBox(150, 120);
    
    createLabel("Doctor ID:", 50, 170);
    createInputBox(150, 170);
    
    createLabel("Date (DD/MM/YYYY):", 50, 220);
    createInputBox(150, 220);
    
    createLabel("Time (HH:MM):", 50, 270);
    createInputBox(150, 270);
    
    createLabel("Notes:", 50, 320);
    createInputBox(150, 320);
    
    createButton("Book Appointment", 150, 400);
    createButton("Cancel", 400, 400);
    
    if (selectedButton >= 0) {
        if (selectedButton == 0) {
            processBookAppointment();
        } else {
            currentScreen = APPOINTMENT_MENU;
        }
        selectedButton = -1;
    }
}

// Create UI elements
void GUI::createButton(const std::string& text, float x, float y, float width, float height) {
    sf::RectangleShape button(sf::Vector2f(width, height));
    button.setPosition(x, y);
    button.setFillColor(buttonColor);
    button.setOutlineColor(sf::Color::Black);
    button.setOutlineThickness(2.0f);
    buttons.push_back(button);
    
    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(18);
    buttonText.setFillColor(textColor);
    buttonText.setPosition(x + width/2 - buttonText.getLocalBounds().width/2, 
                          y + height/2 - buttonText.getLocalBounds().height/2);
    buttonTexts.push_back(buttonText);
}

void GUI::createLabel(const std::string& text, float x, float y, int size) {
    sf::Text label;
    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(size);
    label.setFillColor(textColor);
    label.setPosition(x, y);
    labels.push_back(label);
}

void GUI::createInputBox(float x, float y, float width, float height) {
    sf::RectangleShape inputBox(sf::Vector2f(width, height));
    inputBox.setPosition(x, y);
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(1.0f);
    inputBoxes.push_back(inputBox);
    
    sf::Text inputText;
    inputText.setFont(font);
    inputText.setString("");
    inputText.setCharacterSize(16);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(x + 5, y + 5);
    inputTexts.push_back(inputText);
}

void GUI::clearUI() {
    buttons.clear();
    buttonTexts.clear();
    labels.clear();
    inputBoxes.clear();
    inputTexts.clear();
    currentInputBox = -1;
    currentInput = "";
}

// Utility functions
bool GUI::loadFont() {
    // Try to load a system font or use default
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            // Use default font if system fonts not available
            return true; // SFML will use default font
        }
    }
    return true;
}

void GUI::setColors() {
    backgroundColor = sf::Color(240, 240, 240);
    buttonColor = sf::Color(100, 150, 200);
    textColor = sf::Color::Black;
    highlightColor = sf::Color(255, 255, 0);
}

void GUI::updateInputText() {
    if (currentInputBox >= 0 && currentInputBox < inputTexts.size()) {
        inputTexts[currentInputBox].setString(currentInput);
    }
}

void GUI::drawText(const std::string& text, float x, float y, int size, sf::Color color) {
    sf::Text textObj;
    textObj.setFont(font);
    textObj.setString(text);
    textObj.setCharacterSize(size);
    textObj.setFillColor(color);
    textObj.setPosition(x, y);
    window.draw(textObj);
}

void GUI::drawCenteredText(const std::string& text, float y, int size, sf::Color color) {
    sf::Text textObj;
    textObj.setFont(font);
    textObj.setString(text);
    textObj.setCharacterSize(size);
    textObj.setFillColor(color);
    textObj.setPosition(WINDOW_WIDTH/2 - textObj.getLocalBounds().width/2, y);
    window.draw(textObj);
}

void GUI::drawRectangle(float x, float y, float width, float height, sf::Color fillColor, sf::Color outlineColor, float outlineThickness) {
    sf::RectangleShape rect(sf::Vector2f(width, height));
    rect.setPosition(x, y);
    rect.setFillColor(fillColor);
    rect.setOutlineColor(outlineColor);
    rect.setOutlineThickness(outlineThickness);
    window.draw(rect);
}

// Data display
void GUI::displayPatients() {
    Patient* current = clinic->getPatients().getHead();
    float y = 120;
    int count = 0;
    
    while (current != nullptr && count < 15) { // Limit display to fit screen
        std::ostringstream oss;
        oss << "ID: " << current->getId() << " | " << current->getName() 
            << " | Age: " << current->getAge() << " | Disease: " << current->getDisease();
        
        drawText(oss.str(), 50, y, 14);
        y += 25;
        count++;
        current = current->getNext();
    }
}

void GUI::displayDoctors() {
    Doctor* current = clinic->getDoctors().getHead();
    float y = 120;
    int count = 0;
    
    while (current != nullptr && count < 15) {
        std::ostringstream oss;
        oss << "ID: " << current->getId() << " | Dr. " << current->getName() 
            << " | " << current->getSpecialization() 
            << " | Available: " << (current->getIsAvailable() ? "Yes" : "No");
        
        drawText(oss.str(), 50, y, 14);
        y += 25;
        count++;
        current = current->getNext();
    }
}

void GUI::displayAppointments() {
    Appointment* current = clinic->getAppointments().getFront();
    float y = 120;
    int count = 0;
    
    while (current != nullptr && count < 15) {
        std::ostringstream oss;
        oss << "ID: " << current->getAppointmentId() 
            << " | " << current->getPatientName() << " - Dr. " << current->getDoctorName()
            << " | " << current->getDate() << " " << current->getTime()
            << " | Status: " << current->getStatus();
        
        drawText(oss.str(), 50, y, 14);
        y += 25;
        count++;
        current = current->getNext();
    }
}

// Input processing
void GUI::processAddPatient() {
    if (inputTexts.size() >= 5) {
        std::string name = inputTexts[0].getString();
        int age = std::stoi(inputTexts[1].getString());
        std::string disease = inputTexts[2].getString();
        std::string contact = inputTexts[3].getString();
        std::string address = inputTexts[4].getString();
        
        if (clinic->addPatient(name, age, disease, contact, address)) {
            drawText("Patient added successfully!", 50, 500, 16, sf::Color::Green);
        } else {
            drawText("Error adding patient!", 50, 500, 16, sf::Color::Red);
        }
    }
}

void GUI::processAddDoctor() {
    if (inputTexts.size() >= 4) {
        std::string name = inputTexts[0].getString();
        std::string specialization = inputTexts[1].getString();
        std::string contact = inputTexts[2].getString();
        std::string schedule = inputTexts[3].getString();
        
        if (clinic->addDoctor(name, specialization, contact, schedule)) {
            drawText("Doctor added successfully!", 50, 500, 16, sf::Color::Green);
        } else {
            drawText("Error adding doctor!", 50, 500, 16, sf::Color::Red);
        }
    }
}

void GUI::processBookAppointment() {
    if (inputTexts.size() >= 5) {
        int patientId = std::stoi(inputTexts[0].getString());
        int doctorId = std::stoi(inputTexts[1].getString());
        std::string date = inputTexts[2].getString();
        std::string time = inputTexts[3].getString();
        std::string notes = inputTexts[4].getString();
        
        if (clinic->bookAppointment(patientId, doctorId, date, time, notes)) {
            drawText("Appointment booked successfully!", 50, 500, 16, sf::Color::Green);
        } else {
            drawText("Error booking appointment!", 50, 500, 16, sf::Color::Red);
        }
    }
}

// Getters
bool GUI::isRunning() const {
    return window.isOpen();
}

// Cleanup
void GUI::cleanup() {
    clinic->saveAllData();
}

#endif // SFML_AVAILABLE