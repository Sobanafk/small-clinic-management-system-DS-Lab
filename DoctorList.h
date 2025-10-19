#ifndef DOCTORLIST_H
#define DOCTORLIST_H

#include "Doctor.h"
#include <fstream>
#include <vector>

class DoctorList {
private:
    Doctor* head;
    int count;
    int nextId;

public:
    // Constructor and Destructor
    DoctorList();
    ~DoctorList();
    
    // Basic operations
    void addDoctor(const Doctor& doctor);
    bool removeDoctor(int id);
    Doctor* findDoctor(int id) const;
    Doctor* findDoctorByName(const std::string& name) const;
    void displayAll() const;
    void displayBySpecialization(const std::string& specialization) const;
    void displayAvailable() const;
    
    // Getters
    int getCount() const;
    int getNextId();
    Doctor* getHead() const;
    
    // File operations
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
    
    // Utility functions
    bool isEmpty() const;
    void clear();
    std::vector<Doctor*> searchDoctors(const std::string& searchTerm) const;
    std::vector<Doctor*> getAvailableDoctors() const;
    
    // Copy constructor and assignment operator
    DoctorList(const DoctorList& other);
    DoctorList& operator=(const DoctorList& other);
};

#endif