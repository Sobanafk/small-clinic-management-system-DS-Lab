#ifndef APPOINTMENTQUEUE_H
#define APPOINTMENTQUEUE_H

#include "Appointment.h"
#include <fstream>
#include <vector>

class AppointmentQueue {
private:
    Appointment* front;
    Appointment* rear;
    int count;
    int nextId;

public:
    // Constructor and Destructor
    AppointmentQueue();
    ~AppointmentQueue();
    
    // Queue operations
    void enqueue(const Appointment& appointment);
    bool dequeue();
    Appointment* peek() const;
    bool isEmpty() const;
    int size() const;
    
    // Appointment management
    bool cancelAppointment(int appointmentId);
    bool completeAppointment(int appointmentId);
    Appointment* findAppointment(int appointmentId) const;
    void displayAll() const;
    void displayByPatient(int patientId) const;
    void displayByDoctor(int doctorId) const;
    void displayByStatus(const std::string& status) const;
    
    // Getters
    int getNextId();
    Appointment* getFront() const;
    
    // File operations
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
    
    // Utility functions
    void clear();
    std::vector<Appointment*> searchAppointments(const std::string& searchTerm) const;
    std::vector<Appointment*> getAppointmentsByDate(const std::string& date) const;
    
    // Copy constructor and assignment operator
    AppointmentQueue(const AppointmentQueue& other);
    AppointmentQueue& operator=(const AppointmentQueue& other);
};

#endif