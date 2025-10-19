#ifndef PATIENTLIST_H
#define PATIENTLIST_H

#include "Patient.h"
#include <fstream>
#include <vector>

class PatientList {
private:
    Patient* head;
    int count;
    int nextId;

public:
    // Constructor and Destructor
    PatientList();
    ~PatientList();
    
    // Basic operations
    void addPatient(const Patient& patient);
    bool removePatient(int id);
    Patient* findPatient(int id) const;
    Patient* findPatientByName(const std::string& name) const;
    void displayAll() const;
    void displayByDisease(const std::string& disease) const;
    
    // Getters
    int getCount() const;
    int getNextId();
    Patient* getHead() const;
    
    // File operations
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
    
    // Utility functions
    bool isEmpty() const;
    void clear();
    std::vector<Patient*> searchPatients(const std::string& searchTerm) const;
    
    // Copy constructor and assignment operator (for deep copy)
    PatientList(const PatientList& other);
    PatientList& operator=(const PatientList& other);
};

#endif