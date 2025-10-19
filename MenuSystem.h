#ifndef MENUSYSTEM_H
#define MENUSYSTEM_H

#include "Clinic.h"
#include <iostream>
#include <string>
#include <climits>

class MenuSystem {
private:
    Clinic* clinic;
    
    // Input validation helpers
    int getIntInput(const std::string& prompt, int min = INT_MIN, int max = INT_MAX);
    std::string getStringInput(const std::string& prompt, bool allowEmpty = false);
    std::string getDateInput(const std::string& prompt);
    std::string getTimeInput(const std::string& prompt);
    
    // Patient menu functions
    void patientMenu();
    void addPatientMenu();
    void removePatientMenu();
    void updatePatientMenu();
    void searchPatientMenu();
    void displayPatientsMenu();
    
    // Doctor menu functions
    void doctorMenu();
    void addDoctorMenu();
    void removeDoctorMenu();
    void updateDoctorMenu();
    void searchDoctorMenu();
    void displayDoctorsMenu();
    void toggleDoctorAvailabilityMenu();
    
    // Appointment menu functions
    void appointmentMenu();
    void bookAppointmentMenu();
    void cancelAppointmentMenu();
    void completeAppointmentMenu();
    void searchAppointmentMenu();
    void displayAppointmentsMenu();
    
    // Report menu functions
    void reportMenu();
    void statisticsMenu();
    void patientHistoryMenu();
    void doctorScheduleMenu();
    
    // Utility functions
    void clearScreen();
    void pause();
    void displayHeader(const std::string& title);
    bool confirmAction(const std::string& message);

public:
    // Constructor and Destructor
    MenuSystem();
    ~MenuSystem();
    
    // Main menu functions
    void run();
    void displayMainMenu();
    void handleMainMenuChoice(int choice);
    
    // System functions
    void initializeSystem();
    void shutdownSystem();
};

#endif