#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include <iostream>
#include "Patient.h"
#include "Doctor.h"

class Appointment {
private:
    int appointmentId;
    int patientId;
    int doctorId;
    std::string patientName;
    std::string doctorName;
    std::string date;
    std::string time;
    std::string status; // "Scheduled", "Completed", "Cancelled"
    std::string notes;
    Appointment* next;

public:
    // Constructors
    Appointment();
    Appointment(int appointmentId, int patientId, int doctorId, 
                const std::string& patientName, const std::string& doctorName,
                const std::string& date, const std::string& time, 
                const std::string& status = "Scheduled", const std::string& notes = "");
    
    // Getters
    int getAppointmentId() const;
    int getPatientId() const;
    int getDoctorId() const;
    std::string getPatientName() const;
    std::string getDoctorName() const;
    std::string getDate() const;
    std::string getTime() const;
    std::string getStatus() const;
    std::string getNotes() const;
    Appointment* getNext() const;
    
    // Setters
    void setAppointmentId(int appointmentId);
    void setPatientId(int patientId);
    void setDoctorId(int doctorId);
    void setPatientName(const std::string& patientName);
    void setDoctorName(const std::string& doctorName);
    void setDate(const std::string& date);
    void setTime(const std::string& time);
    void setStatus(const std::string& status);
    void setNotes(const std::string& notes);
    void setNext(Appointment* next);
    
    // Utility functions
    void display() const;
    std::string toString() const;
    bool isValid() const;
    void cancel();
    void complete();
    
    // Friend function for file I/O
    friend std::ostream& operator<<(std::ostream& os, const Appointment& appointment);
    friend std::istream& operator>>(std::istream& is, Appointment& appointment);
};

#endif