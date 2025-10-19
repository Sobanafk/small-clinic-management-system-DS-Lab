#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
#include <iostream>
#include <vector>

class Doctor {
private:
    int id;
    std::string name;
    std::string specialization;
    std::string contactInfo;
    std::string schedule; // e.g., "Monday-Friday 9AM-5PM"
    bool isAvailable;
    Doctor* next;

public:
    // Constructors
    Doctor();
    Doctor(int id, const std::string& name, const std::string& specialization, 
           const std::string& contactInfo, const std::string& schedule, bool isAvailable = true);
    
    // Getters
    int getId() const;
    std::string getName() const;
    std::string getSpecialization() const;
    std::string getContactInfo() const;
    std::string getSchedule() const;
    bool getIsAvailable() const;
    Doctor* getNext() const;
    
    // Setters
    void setId(int id);
    void setName(const std::string& name);
    void setSpecialization(const std::string& specialization);
    void setContactInfo(const std::string& contactInfo);
    void setSchedule(const std::string& schedule);
    void setIsAvailable(bool isAvailable);
    void setNext(Doctor* next);
    
    // Utility functions
    void display() const;
    std::string toString() const;
    bool isValid() const;
    void toggleAvailability();
    
    // Friend function for file I/O
    friend std::ostream& operator<<(std::ostream& os, const Doctor& doctor);
    friend std::istream& operator>>(std::istream& is, Doctor& doctor);
};

#endif