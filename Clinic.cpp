#include "Clinic.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <vector>

// Default constructor
Clinic::Clinic() : patientsFile("patients.txt"), doctorsFile("doctors.txt"), appointmentsFile("appointments.txt") {
    loadAllData();
}

// Parameterized constructor
Clinic::Clinic(const std::string& patientsFile, const std::string& doctorsFile, const std::string& appointmentsFile)
    : patientsFile(patientsFile), doctorsFile(doctorsFile), appointmentsFile(appointmentsFile) {
    loadAllData();
}

// Destructor
Clinic::~Clinic() {
    saveAllData();
}

// Patient Management
bool Clinic::addPatient(const std::string& name, int age, const std::string& disease, 
                       const std::string& contactInfo, const std::string& address) {
    if (name.empty() || age <= 0 || age > 150 || contactInfo.empty()) {
        return false;
    }
    
    Patient patient(0, name, age, disease, contactInfo, address);
    patients.addPatient(patient);
    addToHistory("Added patient: " + name);
    return true;
}

bool Clinic::removePatient(int patientId) {
    Patient* patient = patients.findPatient(patientId);
    if (patient == nullptr) return false;
    
    std::string patientName = patient->getName();
    bool result = patients.removePatient(patientId);
    if (result) {
        addToHistory("Removed patient: " + patientName);
    }
    return result;
}

bool Clinic::updatePatient(int patientId, const std::string& name, int age, const std::string& disease, 
                          const std::string& contactInfo, const std::string& address) {
    Patient* patient = patients.findPatient(patientId);
    if (patient == nullptr) return false;
    
    if (name.empty() || age <= 0 || age > 150 || contactInfo.empty()) {
        return false;
    }
    
    patient->setName(name);
    patient->setAge(age);
    patient->setDisease(disease);
    patient->setContactInfo(contactInfo);
    patient->setAddress(address);
    
    addToHistory("Updated patient: " + name);
    return true;
}

Patient* Clinic::findPatient(int patientId) {
    return patients.findPatient(patientId);
}

Patient* Clinic::findPatientByName(const std::string& name) {
    return patients.findPatientByName(name);
}

void Clinic::displayAllPatients() const {
    patients.displayAll();
}

void Clinic::displayPatientsByDisease(const std::string& disease) const {
    patients.displayByDisease(disease);
}

std::vector<Patient*> Clinic::searchPatients(const std::string& searchTerm) const {
    return patients.searchPatients(searchTerm);
}

// Doctor Management
bool Clinic::addDoctor(const std::string& name, const std::string& specialization, 
                      const std::string& contactInfo, const std::string& schedule) {
    if (name.empty() || specialization.empty() || contactInfo.empty()) {
        return false;
    }
    
    Doctor doctor(0, name, specialization, contactInfo, schedule, true);
    doctors.addDoctor(doctor);
    addToHistory("Added doctor: Dr. " + name);
    return true;
}

bool Clinic::removeDoctor(int doctorId) {
    Doctor* doctor = doctors.findDoctor(doctorId);
    if (doctor == nullptr) return false;
    
    std::string doctorName = doctor->getName();
    bool result = doctors.removeDoctor(doctorId);
    if (result) {
        addToHistory("Removed doctor: Dr. " + doctorName);
    }
    return result;
}

bool Clinic::updateDoctor(int doctorId, const std::string& name, const std::string& specialization, 
                         const std::string& contactInfo, const std::string& schedule) {
    Doctor* doctor = doctors.findDoctor(doctorId);
    if (doctor == nullptr) return false;
    
    if (name.empty() || specialization.empty() || contactInfo.empty()) {
        return false;
    }
    
    doctor->setName(name);
    doctor->setSpecialization(specialization);
    doctor->setContactInfo(contactInfo);
    doctor->setSchedule(schedule);
    
    addToHistory("Updated doctor: Dr. " + name);
    return true;
}

Doctor* Clinic::findDoctor(int doctorId) {
    return doctors.findDoctor(doctorId);
}

Doctor* Clinic::findDoctorByName(const std::string& name) {
    return doctors.findDoctorByName(name);
}

void Clinic::displayAllDoctors() const {
    doctors.displayAll();
}

void Clinic::displayDoctorsBySpecialization(const std::string& specialization) const {
    doctors.displayBySpecialization(specialization);
}

void Clinic::displayAvailableDoctors() const {
    doctors.displayAvailable();
}

std::vector<Doctor*> Clinic::searchDoctors(const std::string& searchTerm) const {
    return doctors.searchDoctors(searchTerm);
}

bool Clinic::toggleDoctorAvailability(int doctorId) {
    Doctor* doctor = doctors.findDoctor(doctorId);
    if (doctor == nullptr) return false;
    
    doctor->toggleAvailability();
    addToHistory("Toggled availability for Dr. " + doctor->getName());
    return true;
}

// Appointment Management
bool Clinic::bookAppointment(int patientId, int doctorId, const std::string& date, 
                            const std::string& time, const std::string& notes) {
    Patient* patient = patients.findPatient(patientId);
    Doctor* doctor = doctors.findDoctor(doctorId);
    
    if (patient == nullptr || doctor == nullptr) {
        return false;
    }
    
    if (!doctor->getIsAvailable()) {
        return false;
    }
    
    if (!isValidDate(date) || !isValidTime(time)) {
        return false;
    }
    
    if (!isDoctorAvailable(doctorId, date, time)) {
        return false;
    }
    
    Appointment appointment(0, patientId, doctorId, patient->getName(), 
                          doctor->getName(), date, time, "Scheduled", notes);
    appointments.enqueue(appointment);
    
    addToHistory("Booked appointment for " + patient->getName() + " with Dr. " + doctor->getName());
    return true;
}

bool Clinic::cancelAppointment(int appointmentId) {
    bool result = appointments.cancelAppointment(appointmentId);
    if (result) {
        addToHistory("Cancelled appointment ID: " + std::to_string(appointmentId));
    }
    return result;
}

bool Clinic::completeAppointment(int appointmentId) {
    bool result = appointments.completeAppointment(appointmentId);
    if (result) {
        addToHistory("Completed appointment ID: " + std::to_string(appointmentId));
    }
    return result;
}

Appointment* Clinic::findAppointment(int appointmentId) {
    return appointments.findAppointment(appointmentId);
}

void Clinic::displayAllAppointments() const {
    appointments.displayAll();
}

void Clinic::displayAppointmentsByPatient(int patientId) const {
    appointments.displayByPatient(patientId);
}

void Clinic::displayAppointmentsByDoctor(int doctorId) const {
    appointments.displayByDoctor(doctorId);
}

void Clinic::displayAppointmentsByStatus(const std::string& status) const {
    appointments.displayByStatus(status);
}

void Clinic::displayAppointmentsByDate(const std::string& date) const {
    std::vector<Appointment*> appointmentsByDate = appointments.getAppointmentsByDate(date);
    if (appointmentsByDate.empty()) {
        std::cout << "No appointments found for date: " << date << std::endl;
        return;
    }
    
    int index = 1;
    for (Appointment* appointment : appointmentsByDate) {
        std::cout << "\n--- Appointment " << index << " ---" << std::endl;
        appointment->display();
        index++;
    }
}

std::vector<Appointment*> Clinic::searchAppointments(const std::string& searchTerm) const {
    return appointments.searchAppointments(searchTerm);
}

// Statistics and Reports
void Clinic::displayStatistics() const {
    std::cout << "\n=== CLINIC STATISTICS ===" << std::endl;
    std::cout << "Total Patients: " << patients.getCount() << std::endl;
    std::cout << "Total Doctors: " << doctors.getCount() << std::endl;
    std::cout << "Total Appointments: " << appointments.size() << std::endl;
    
    // Count appointments by status
    int scheduled = 0, completed = 0, cancelled = 0;
    Appointment* current = appointments.getFront();
    while (current != nullptr) {
        if (current->getStatus() == "Scheduled") scheduled++;
        else if (current->getStatus() == "Completed") completed++;
        else if (current->getStatus() == "Cancelled") cancelled++;
        current = current->getNext();
    }
    
    std::cout << "Scheduled Appointments: " << scheduled << std::endl;
    std::cout << "Completed Appointments: " << completed << std::endl;
    std::cout << "Cancelled Appointments: " << cancelled << std::endl;
    std::cout << "=========================" << std::endl;
}

void Clinic::displayPatientHistory(int patientId) const {
    Patient* patient = patients.findPatient(patientId);
    if (patient == nullptr) {
        std::cout << "Patient not found." << std::endl;
        return;
    }
    
    std::cout << "\n=== PATIENT HISTORY ===" << std::endl;
    patient->display();
    std::cout << "\nAppointments:" << std::endl;
    appointments.displayByPatient(patientId);
    std::cout << "======================" << std::endl;
}

void Clinic::displayDoctorSchedule(int doctorId) const {
    Doctor* doctor = doctors.findDoctor(doctorId);
    if (doctor == nullptr) {
        std::cout << "Doctor not found." << std::endl;
        return;
    }
    
    std::cout << "\n=== DOCTOR SCHEDULE ===" << std::endl;
    doctor->display();
    std::cout << "\nAppointments:" << std::endl;
    appointments.displayByDoctor(doctorId);
    std::cout << "=======================" << std::endl;
}

// File Operations
bool Clinic::saveAllData() const {
    return savePatients() && saveDoctors() && saveAppointments();
}

bool Clinic::loadAllData() {
    return loadPatients() && loadDoctors() && loadAppointments();
}

bool Clinic::savePatients() const {
    return patients.saveToFile(patientsFile);
}

bool Clinic::loadPatients() {
    return patients.loadFromFile(patientsFile);
}

bool Clinic::saveDoctors() const {
    return doctors.saveToFile(doctorsFile);
}

bool Clinic::loadDoctors() {
    return doctors.loadFromFile(doctorsFile);
}

bool Clinic::saveAppointments() const {
    return appointments.saveToFile(appointmentsFile);
}

bool Clinic::loadAppointments() {
    return appointments.loadFromFile(appointmentsFile);
}

// Utility Functions
bool Clinic::isValidDate(const std::string& date) const {
    // Simple date validation (DD/MM/YYYY format)
    if (date.length() != 10) return false;
    if (date[2] != '/' || date[5] != '/') return false;
    
    int day = std::stoi(date.substr(0, 2));
    int month = std::stoi(date.substr(3, 2));
    int year = std::stoi(date.substr(6, 4));
    
    if (day < 1 || day > 31) return false;
    if (month < 1 || month > 12) return false;
    if (year < 2024) return false;
    
    return true;
}

bool Clinic::isValidTime(const std::string& time) const {
    // Simple time validation (HH:MM format)
    if (time.length() != 5) return false;
    if (time[2] != ':') return false;
    
    int hour = std::stoi(time.substr(0, 2));
    int minute = std::stoi(time.substr(3, 2));
    
    if (hour < 0 || hour > 23) return false;
    if (minute < 0 || minute > 59) return false;
    
    return true;
}

bool Clinic::isDoctorAvailable(int doctorId, const std::string& date, const std::string& time) const {
    // Check if doctor has conflicting appointments
    std::vector<Appointment*> doctorAppointments = appointments.getAppointmentsByDate(date);
    
    for (Appointment* appointment : doctorAppointments) {
        if (appointment->getDoctorId() == doctorId && 
            appointment->getTime() == time && 
            appointment->getStatus() == "Scheduled") {
            return false;
        }
    }
    
    return true;
}

void Clinic::addToHistory(const std::string& operation) {
    operationHistory.push(operation);
    
    // Keep only last 50 operations
    if (operationHistory.size() > 50) {
        std::stack<std::string> temp;
        for (int i = 0; i < 49; i++) {
            temp.push(operationHistory.top());
            operationHistory.pop();
        }
        operationHistory = temp;
    }
}

void Clinic::displayHistory() const {
    std::cout << "\n=== OPERATION HISTORY ===" << std::endl;
    std::stack<std::string> temp = operationHistory;
    int count = 1;
    
    while (!temp.empty()) {
        std::cout << count << ". " << temp.top() << std::endl;
        temp.pop();
        count++;
    }
    
    if (operationHistory.empty()) {
        std::cout << "No operations recorded." << std::endl;
    }
    std::cout << "=========================" << std::endl;
}

// Getters
int Clinic::getPatientCount() const { return patients.getCount(); }
int Clinic::getDoctorCount() const { return doctors.getCount(); }
int Clinic::getAppointmentCount() const { return appointments.size(); }
PatientList& Clinic::getPatients() { return patients; }
DoctorList& Clinic::getDoctors() { return doctors; }
AppointmentQueue& Clinic::getAppointments() { return appointments; }