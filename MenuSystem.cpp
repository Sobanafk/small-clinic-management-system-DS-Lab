#include "MenuSystem.h"
#include <limits>
#include <cstdlib>
#include <iomanip>

// Constructor
MenuSystem::MenuSystem() : clinic(nullptr) {
    clinic = new Clinic();
}

// Destructor
MenuSystem::~MenuSystem() {
    delete clinic;
}

// Main run function
void MenuSystem::run() {
    initializeSystem();
    
    int choice;
    do {
        displayMainMenu();
        choice = getIntInput("Enter your choice (1-8): ", 1, 8);
        handleMainMenuChoice(choice);
    } while (choice != 8);
    
    shutdownSystem();
}

// Display main menu
void MenuSystem::displayMainMenu() {
    clearScreen();
    displayHeader("SMALL CLINIC MANAGEMENT SYSTEM");
    
    std::cout << "1. Patient Management" << std::endl;
    std::cout << "2. Doctor Management" << std::endl;
    std::cout << "3. Appointment Management" << std::endl;
    std::cout << "4. Reports & Statistics" << std::endl;
    std::cout << "5. Operation History" << std::endl;
    std::cout << "6. System Statistics" << std::endl;
    std::cout << "7. Save All Data" << std::endl;
    std::cout << "8. Exit" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

// Handle main menu choice
void MenuSystem::handleMainMenuChoice(int choice) {
    switch (choice) {
        case 1:
            patientMenu();
            break;
        case 2:
            doctorMenu();
            break;
        case 3:
            appointmentMenu();
            break;
        case 4:
            reportMenu();
            break;
        case 5:
            clinic->displayHistory();
            pause();
            break;
        case 6:
            clinic->displayStatistics();
            pause();
            break;
        case 7:
            if (clinic->saveAllData()) {
                std::cout << "All data saved successfully!" << std::endl;
            } else {
                std::cout << "Error saving data!" << std::endl;
            }
            pause();
            break;
        case 8:
            std::cout << "Thank you for using the Clinic Management System!" << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            pause();
    }
}

// Patient Menu
void MenuSystem::patientMenu() {
    int choice;
    do {
        clearScreen();
        displayHeader("PATIENT MANAGEMENT");
        
        std::cout << "1. Add New Patient" << std::endl;
        std::cout << "2. Remove Patient" << std::endl;
        std::cout << "3. Update Patient Information" << std::endl;
        std::cout << "4. Search Patient" << std::endl;
        std::cout << "5. Display All Patients" << std::endl;
        std::cout << "6. Display Patients by Disease" << std::endl;
        std::cout << "7. Back to Main Menu" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        
        choice = getIntInput("Enter your choice (1-7): ", 1, 7);
        
        switch (choice) {
            case 1: addPatientMenu(); break;
            case 2: removePatientMenu(); break;
            case 3: updatePatientMenu(); break;
            case 4: searchPatientMenu(); break;
            case 5: displayPatientsMenu(); break;
            case 6: {
                std::string disease = getStringInput("Enter disease name: ");
                clinic->displayPatientsByDisease(disease);
                pause();
                break;
            }
        }
    } while (choice != 7);
}

// Add Patient Menu
void MenuSystem::addPatientMenu() {
    clearScreen();
    displayHeader("ADD NEW PATIENT");
    
    std::string name = getStringInput("Enter patient name: ");
    int age = getIntInput("Enter patient age: ", 1, 150);
    std::string disease = getStringInput("Enter disease/condition: ", true);
    std::string contact = getStringInput("Enter contact information: ");
    std::string address = getStringInput("Enter address: ", true);
    
    if (clinic->addPatient(name, age, disease, contact, address)) {
        std::cout << "Patient added successfully!" << std::endl;
    } else {
        std::cout << "Error adding patient. Please check your input." << std::endl;
    }
    pause();
}

// Remove Patient Menu
void MenuSystem::removePatientMenu() {
    clearScreen();
    displayHeader("REMOVE PATIENT");
    
    int patientId = getIntInput("Enter patient ID to remove: ");
    
    if (confirmAction("Are you sure you want to remove this patient?")) {
        if (clinic->removePatient(patientId)) {
            std::cout << "Patient removed successfully!" << std::endl;
        } else {
            std::cout << "Patient not found or could not be removed." << std::endl;
        }
    } else {
        std::cout << "Operation cancelled." << std::endl;
    }
    pause();
}

// Update Patient Menu
void MenuSystem::updatePatientMenu() {
    clearScreen();
    displayHeader("UPDATE PATIENT INFORMATION");
    
    int patientId = getIntInput("Enter patient ID to update: ");
    Patient* patient = clinic->findPatient(patientId);
    
    if (patient == nullptr) {
        std::cout << "Patient not found!" << std::endl;
        pause();
        return;
    }
    
    std::cout << "Current patient information:" << std::endl;
    patient->display();
    
    std::string name = getStringInput("Enter new name (or press Enter to keep current): ");
    if (name.empty()) name = patient->getName();
    
    int age = getIntInput("Enter new age (or -1 to keep current): ");
    if (age == -1) age = patient->getAge();
    
    std::string disease = getStringInput("Enter new disease (or press Enter to keep current): ");
    if (disease.empty()) disease = patient->getDisease();
    
    std::string contact = getStringInput("Enter new contact (or press Enter to keep current): ");
    if (contact.empty()) contact = patient->getContactInfo();
    
    std::string address = getStringInput("Enter new address (or press Enter to keep current): ");
    if (address.empty()) address = patient->getAddress();
    
    if (clinic->updatePatient(patientId, name, age, disease, contact, address)) {
        std::cout << "Patient updated successfully!" << std::endl;
    } else {
        std::cout << "Error updating patient." << std::endl;
    }
    pause();
}

// Search Patient Menu
void MenuSystem::searchPatientMenu() {
    clearScreen();
    displayHeader("SEARCH PATIENT");
    
    std::string searchTerm = getStringInput("Enter search term (name, disease, or contact): ");
    std::vector<Patient*> results = clinic->searchPatients(searchTerm);
    
    if (results.empty()) {
        std::cout << "No patients found matching your search." << std::endl;
    } else {
        std::cout << "Found " << results.size() << " patient(s):" << std::endl;
        for (Patient* patient : results) {
            patient->display();
        }
    }
    pause();
}

// Display Patients Menu
void MenuSystem::displayPatientsMenu() {
    clearScreen();
    displayHeader("ALL PATIENTS");
    clinic->displayAllPatients();
    pause();
}

// Doctor Menu
void MenuSystem::doctorMenu() {
    int choice;
    do {
        clearScreen();
        displayHeader("DOCTOR MANAGEMENT");
        
        std::cout << "1. Add New Doctor" << std::endl;
        std::cout << "2. Remove Doctor" << std::endl;
        std::cout << "3. Update Doctor Information" << std::endl;
        std::cout << "4. Search Doctor" << std::endl;
        std::cout << "5. Display All Doctors" << std::endl;
        std::cout << "6. Display Doctors by Specialization" << std::endl;
        std::cout << "7. Display Available Doctors" << std::endl;
        std::cout << "8. Toggle Doctor Availability" << std::endl;
        std::cout << "9. Back to Main Menu" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        
        choice = getIntInput("Enter your choice (1-9): ", 1, 9);
        
        switch (choice) {
            case 1: addDoctorMenu(); break;
            case 2: removeDoctorMenu(); break;
            case 3: updateDoctorMenu(); break;
            case 4: searchDoctorMenu(); break;
            case 5: displayDoctorsMenu(); break;
            case 6: {
                std::string specialization = getStringInput("Enter specialization: ");
                clinic->displayDoctorsBySpecialization(specialization);
                pause();
                break;
            }
            case 7: {
                clinic->displayAvailableDoctors();
                pause();
                break;
            }
            case 8: toggleDoctorAvailabilityMenu(); break;
        }
    } while (choice != 9);
}

// Add Doctor Menu
void MenuSystem::addDoctorMenu() {
    clearScreen();
    displayHeader("ADD NEW DOCTOR");
    
    std::string name = getStringInput("Enter doctor name: ");
    std::string specialization = getStringInput("Enter specialization: ");
    std::string contact = getStringInput("Enter contact information: ");
    std::string schedule = getStringInput("Enter schedule (e.g., Monday-Friday 9AM-5PM): ");
    
    if (clinic->addDoctor(name, specialization, contact, schedule)) {
        std::cout << "Doctor added successfully!" << std::endl;
    } else {
        std::cout << "Error adding doctor. Please check your input." << std::endl;
    }
    pause();
}

// Remove Doctor Menu
void MenuSystem::removeDoctorMenu() {
    clearScreen();
    displayHeader("REMOVE DOCTOR");
    
    int doctorId = getIntInput("Enter doctor ID to remove: ");
    
    if (confirmAction("Are you sure you want to remove this doctor?")) {
        if (clinic->removeDoctor(doctorId)) {
            std::cout << "Doctor removed successfully!" << std::endl;
        } else {
            std::cout << "Doctor not found or could not be removed." << std::endl;
        }
    } else {
        std::cout << "Operation cancelled." << std::endl;
    }
    pause();
}

// Update Doctor Menu
void MenuSystem::updateDoctorMenu() {
    clearScreen();
    displayHeader("UPDATE DOCTOR INFORMATION");
    
    int doctorId = getIntInput("Enter doctor ID to update: ");
    Doctor* doctor = clinic->findDoctor(doctorId);
    
    if (doctor == nullptr) {
        std::cout << "Doctor not found!" << std::endl;
        pause();
        return;
    }
    
    std::cout << "Current doctor information:" << std::endl;
    doctor->display();
    
    std::string name = getStringInput("Enter new name (or press Enter to keep current): ");
    if (name.empty()) name = doctor->getName();
    
    std::string specialization = getStringInput("Enter new specialization (or press Enter to keep current): ");
    if (specialization.empty()) specialization = doctor->getSpecialization();
    
    std::string contact = getStringInput("Enter new contact (or press Enter to keep current): ");
    if (contact.empty()) contact = doctor->getContactInfo();
    
    std::string schedule = getStringInput("Enter new schedule (or press Enter to keep current): ");
    if (schedule.empty()) schedule = doctor->getSchedule();
    
    if (clinic->updateDoctor(doctorId, name, specialization, contact, schedule)) {
        std::cout << "Doctor updated successfully!" << std::endl;
    } else {
        std::cout << "Error updating doctor." << std::endl;
    }
    pause();
}

// Search Doctor Menu
void MenuSystem::searchDoctorMenu() {
    clearScreen();
    displayHeader("SEARCH DOCTOR");
    
    std::string searchTerm = getStringInput("Enter search term (name, specialization, or contact): ");
    std::vector<Doctor*> results = clinic->searchDoctors(searchTerm);
    
    if (results.empty()) {
        std::cout << "No doctors found matching your search." << std::endl;
    } else {
        std::cout << "Found " << results.size() << " doctor(s):" << std::endl;
        for (Doctor* doctor : results) {
            doctor->display();
        }
    }
    pause();
}

// Display Doctors Menu
void MenuSystem::displayDoctorsMenu() {
    clearScreen();
    displayHeader("ALL DOCTORS");
    clinic->displayAllDoctors();
    pause();
}

// Toggle Doctor Availability Menu
void MenuSystem::toggleDoctorAvailabilityMenu() {
    clearScreen();
    displayHeader("TOGGLE DOCTOR AVAILABILITY");
    
    int doctorId = getIntInput("Enter doctor ID: ");
    Doctor* doctor = clinic->findDoctor(doctorId);
    
    if (doctor == nullptr) {
        std::cout << "Doctor not found!" << std::endl;
    } else {
        std::cout << "Current availability: " << (doctor->getIsAvailable() ? "Available" : "Not Available") << std::endl;
        if (confirmAction("Do you want to toggle availability?")) {
            if (clinic->toggleDoctorAvailability(doctorId)) {
                std::cout << "Doctor availability toggled successfully!" << std::endl;
            } else {
                std::cout << "Error toggling availability." << std::endl;
            }
        }
    }
    pause();
}

// Appointment Menu
void MenuSystem::appointmentMenu() {
    int choice;
    do {
        clearScreen();
        displayHeader("APPOINTMENT MANAGEMENT");
        
        std::cout << "1. Book New Appointment" << std::endl;
        std::cout << "2. Cancel Appointment" << std::endl;
        std::cout << "3. Complete Appointment" << std::endl;
        std::cout << "4. Search Appointment" << std::endl;
        std::cout << "5. Display All Appointments" << std::endl;
        std::cout << "6. Display Appointments by Patient" << std::endl;
        std::cout << "7. Display Appointments by Doctor" << std::endl;
        std::cout << "8. Display Appointments by Status" << std::endl;
        std::cout << "9. Display Appointments by Date" << std::endl;
        std::cout << "10. Back to Main Menu" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        
        choice = getIntInput("Enter your choice (1-10): ", 1, 10);
        
        switch (choice) {
            case 1: bookAppointmentMenu(); break;
            case 2: cancelAppointmentMenu(); break;
            case 3: completeAppointmentMenu(); break;
            case 4: searchAppointmentMenu(); break;
            case 5: displayAppointmentsMenu(); break;
            case 6: {
                int patientId = getIntInput("Enter patient ID: ");
                clinic->displayAppointmentsByPatient(patientId);
                pause();
                break;
            }
            case 7: {
                int doctorId = getIntInput("Enter doctor ID: ");
                clinic->displayAppointmentsByDoctor(doctorId);
                pause();
                break;
            }
            case 8: {
                std::string status = getStringInput("Enter status (Scheduled/Completed/Cancelled): ");
                clinic->displayAppointmentsByStatus(status);
                pause();
                break;
            }
            case 9: {
                std::string date = getDateInput("Enter date (DD/MM/YYYY): ");
                clinic->displayAppointmentsByDate(date);
                pause();
                break;
            }
        }
    } while (choice != 10);
}

// Book Appointment Menu
void MenuSystem::bookAppointmentMenu() {
    clearScreen();
    displayHeader("BOOK NEW APPOINTMENT");
    
    int patientId = getIntInput("Enter patient ID: ");
    Patient* patient = clinic->findPatient(patientId);
    if (patient == nullptr) {
        std::cout << "Patient not found!" << std::endl;
        pause();
        return;
    }
    
    int doctorId = getIntInput("Enter doctor ID: ");
    Doctor* doctor = clinic->findDoctor(doctorId);
    if (doctor == nullptr) {
        std::cout << "Doctor not found!" << std::endl;
        pause();
        return;
    }
    
    if (!doctor->getIsAvailable()) {
        std::cout << "Doctor is not available!" << std::endl;
        pause();
        return;
    }
    
    std::string date = getDateInput("Enter appointment date (DD/MM/YYYY): ");
    std::string time = getTimeInput("Enter appointment time (HH:MM): ");
    std::string notes = getStringInput("Enter notes (optional): ", true);
    
    if (clinic->bookAppointment(patientId, doctorId, date, time, notes)) {
        std::cout << "Appointment booked successfully!" << std::endl;
    } else {
        std::cout << "Error booking appointment. Please check your input or doctor availability." << std::endl;
    }
    pause();
}

// Cancel Appointment Menu
void MenuSystem::cancelAppointmentMenu() {
    clearScreen();
    displayHeader("CANCEL APPOINTMENT");
    
    int appointmentId = getIntInput("Enter appointment ID to cancel: ");
    
    if (confirmAction("Are you sure you want to cancel this appointment?")) {
        if (clinic->cancelAppointment(appointmentId)) {
            std::cout << "Appointment cancelled successfully!" << std::endl;
        } else {
            std::cout << "Appointment not found or could not be cancelled." << std::endl;
        }
    } else {
        std::cout << "Operation cancelled." << std::endl;
    }
    pause();
}

// Complete Appointment Menu
void MenuSystem::completeAppointmentMenu() {
    clearScreen();
    displayHeader("COMPLETE APPOINTMENT");
    
    int appointmentId = getIntInput("Enter appointment ID to complete: ");
    
    if (clinic->completeAppointment(appointmentId)) {
        std::cout << "Appointment completed successfully!" << std::endl;
    } else {
        std::cout << "Appointment not found or could not be completed." << std::endl;
    }
    pause();
}

// Search Appointment Menu
void MenuSystem::searchAppointmentMenu() {
    clearScreen();
    displayHeader("SEARCH APPOINTMENT");
    
    std::string searchTerm = getStringInput("Enter search term: ");
    std::vector<Appointment*> results = clinic->searchAppointments(searchTerm);
    
    if (results.empty()) {
        std::cout << "No appointments found matching your search." << std::endl;
    } else {
        std::cout << "Found " << results.size() << " appointment(s):" << std::endl;
        for (Appointment* appointment : results) {
            appointment->display();
        }
    }
    pause();
}

// Display Appointments Menu
void MenuSystem::displayAppointmentsMenu() {
    clearScreen();
    displayHeader("ALL APPOINTMENTS");
    clinic->displayAllAppointments();
    pause();
}

// Report Menu
void MenuSystem::reportMenu() {
    int choice;
    do {
        clearScreen();
        displayHeader("REPORTS & STATISTICS");
        
        std::cout << "1. System Statistics" << std::endl;
        std::cout << "2. Patient History" << std::endl;
        std::cout << "3. Doctor Schedule" << std::endl;
        std::cout << "4. Back to Main Menu" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        
        choice = getIntInput("Enter your choice (1-4): ", 1, 4);
        
        switch (choice) {
            case 1: statisticsMenu(); break;
            case 2: patientHistoryMenu(); break;
            case 3: doctorScheduleMenu(); break;
        }
    } while (choice != 4);
}

// Statistics Menu
void MenuSystem::statisticsMenu() {
    clearScreen();
    displayHeader("SYSTEM STATISTICS");
    clinic->displayStatistics();
    pause();
}

// Patient History Menu
void MenuSystem::patientHistoryMenu() {
    clearScreen();
    displayHeader("PATIENT HISTORY");
    
    int patientId = getIntInput("Enter patient ID: ");
    clinic->displayPatientHistory(patientId);
    pause();
}

// Doctor Schedule Menu
void MenuSystem::doctorScheduleMenu() {
    clearScreen();
    displayHeader("DOCTOR SCHEDULE");
    
    int doctorId = getIntInput("Enter doctor ID: ");
    clinic->displayDoctorSchedule(doctorId);
    pause();
}

// Input validation helpers
int MenuSystem::getIntInput(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= min && value <= max) {
            std::cin.ignore();
            return value;
        } else {
            std::cout << "Invalid input. Please enter a number between " << min << " and " << max << "." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

std::string MenuSystem::getStringInput(const std::string& prompt, bool allowEmpty) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        
        if (allowEmpty || !input.empty()) {
            return input;
        } else {
            std::cout << "Input cannot be empty. Please try again." << std::endl;
        }
    }
}

std::string MenuSystem::getDateInput(const std::string& prompt) {
    std::string date;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, date);
        
        if (clinic->isValidDate(date)) {
            return date;
        } else {
            std::cout << "Invalid date format. Please use DD/MM/YYYY format." << std::endl;
        }
    }
}

std::string MenuSystem::getTimeInput(const std::string& prompt) {
    std::string time;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, time);
        
        if (clinic->isValidTime(time)) {
            return time;
        } else {
            std::cout << "Invalid time format. Please use HH:MM format." << std::endl;
        }
    }
}

// Utility functions
void MenuSystem::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void MenuSystem::pause() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
}

void MenuSystem::displayHeader(const std::string& title) {
    std::cout << std::string(50, '=') << std::endl;
    std::cout << std::setw(25 + title.length()/2) << title << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

bool MenuSystem::confirmAction(const std::string& message) {
    std::string response;
    std::cout << message << " (y/n): ";
    std::getline(std::cin, response);
    return (response == "y" || response == "Y" || response == "yes" || response == "YES");
}

// System functions
void MenuSystem::initializeSystem() {
    clearScreen();
    std::cout << "Initializing Clinic Management System..." << std::endl;
    std::cout << "Loading data from files..." << std::endl;
    
    if (clinic->loadAllData()) {
        std::cout << "Data loaded successfully!" << std::endl;
    } else {
        std::cout << "No existing data found. Starting with empty system." << std::endl;
    }
    
    std::cout << "System ready!" << std::endl;
    pause();
}

void MenuSystem::shutdownSystem() {
    std::cout << "Saving all data..." << std::endl;
    if (clinic->saveAllData()) {
        std::cout << "Data saved successfully!" << std::endl;
    } else {
        std::cout << "Error saving data!" << std::endl;
    }
}