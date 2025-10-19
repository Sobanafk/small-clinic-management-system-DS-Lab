#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <iostream>

class Patient {
private:
    int id;
    std::string name;
    int age;
    std::string disease;
    std::string contactInfo;
    std::string address;
    Patient* next;

public:
    // Constructors
    Patient();
    Patient(int id, const std::string& name, int age, const std::string& disease, 
            const std::string& contactInfo, const std::string& address);
    
    // Getters
    int getId() const;
    std::string getName() const;
    int getAge() const;
    std::string getDisease() const;
    std::string getContactInfo() const;
    std::string getAddress() const;
    Patient* getNext() const;
    
    // Setters
    void setId(int id);
    void setName(const std::string& name);
    void setAge(int age);
    void setDisease(const std::string& disease);
    void setContactInfo(const std::string& contactInfo);
    void setAddress(const std::string& address);
    void setNext(Patient* next);
    
    // Utility functions
    void display() const;
    std::string toString() const;
    bool isValid() const;
    
    // Friend function for file I/O
    friend std::ostream& operator<<(std::ostream& os, const Patient& patient);
    friend std::istream& operator>>(std::istream& is, Patient& patient);
};

#endif