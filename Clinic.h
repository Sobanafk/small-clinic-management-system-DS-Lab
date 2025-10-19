#ifndef CLINIC_H
#define CLINIC_H

#include "PatientList.h"
#include "DoctorList.h"
#include "AppointmentQueue.h"
#include <string>
#include <stack>

class Clinic {
private:
    PatientList patients;
    DoctorList doctors;
    AppointmentQueue appointments;
    std::stack<std::string> operationHistory; // For undo functionality
    
    // File paths
    std::string patientsFile;
    std::string doctorsFile;
    std::string appointmentsFile;

public:
    // Constructor and Destructor
    Clinic();
    Clinic(const std::string& patientsFile, const std::string& doctorsFile, const std::string& appointmentsFile);
    ~Clinic();
    
    // Patient Management
    bool addPatient(const std::string& name, int age, const std::string& disease, 
                   const std::string& contactInfo, const std::string& address);
    bool removePatient(int patientId);
    bool updatePatient(int patientId, const std::string& name, int age, const std::string& disease, 
                      const std::string& contactInfo, const std::string& address);
    Patient* findPatient(int patientId);
    Patient* findPatientByName(const std::string& name);
    void displayAllPatients() const;
    void displayPatientsByDisease(const std::string& disease) const;
    std::vector<Patient*> searchPatients(const std::string& searchTerm) const;
    
    // Doctor Management
    bool addDoctor(const std::string& name, const std::string& specialization, 
                  const std::string& contactInfo, const std::string& schedule);
    bool removeDoctor(int doctorId);
    bool updateDoctor(int doctorId, const std::string& name, const std::string& specialization, 
                     const std::string& contactInfo, const std::string& schedule);
    Doctor* findDoctor(int doctorId);
    Doctor* findDoctorByName(const std::string& name);
    void displayAllDoctors() const;
    void displayDoctorsBySpecialization(const std::string& specialization) const;
    void displayAvailableDoctors() const;
    std::vector<Doctor*> searchDoctors(const std::string& searchTerm) const;
    bool toggleDoctorAvailability(int doctorId);
    
    // Appointment Management
    bool bookAppointment(int patientId, int doctorId, const std::string& date, 
                        const std::string& time, const std::string& notes = "");
    bool cancelAppointment(int appointmentId);
    bool completeAppointment(int appointmentId);
    Appointment* findAppointment(int appointmentId);
    void displayAllAppointments() const;
    void displayAppointmentsByPatient(int patientId) const;
    void displayAppointmentsByDoctor(int doctorId) const;
    void displayAppointmentsByStatus(const std::string& status) const;
    void displayAppointmentsByDate(const std::string& date) const;
    std::vector<Appointment*> searchAppointments(const std::string& searchTerm) const;
    
    // Statistics and Reports
    void displayStatistics() const;
    void displayPatientHistory(int patientId) const;
    void displayDoctorSchedule(int doctorId) const;
    
    // File Operations
    bool saveAllData() const;
    bool loadAllData();
    bool savePatients() const;
    bool loadPatients();
    bool saveDoctors() const;
    bool loadDoctors();
    bool saveAppointments() const;
    bool loadAppointments();
    
    // Utility Functions
    bool isValidDate(const std::string& date) const;
    bool isValidTime(const std::string& time) const;
    bool isDoctorAvailable(int doctorId, const std::string& date, const std::string& time) const;
    void addToHistory(const std::string& operation);
    void displayHistory() const;
    
    // Getters
    int getPatientCount() const;
    int getDoctorCount() const;
    int getAppointmentCount() const;
    PatientList& getPatients();
    DoctorList& getDoctors();
    AppointmentQueue& getAppointments();
};

#endif