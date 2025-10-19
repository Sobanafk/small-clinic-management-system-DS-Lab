#include "PatientList.h"
#include <iostream>
#include <algorithm>
#include <vector>

// Constructor
PatientList::PatientList() : head(nullptr), count(0), nextId(1) {}

// Destructor
PatientList::~PatientList() {
    clear();
}

// Add patient to the list
void PatientList::addPatient(const Patient& patient) {
    Patient* newPatient = new Patient(patient);
    newPatient->setId(nextId++);
    
    if (head == nullptr) {
        head = newPatient;
    } else {
        Patient* current = head;
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        current->setNext(newPatient);
    }
    count++;
}

// Remove patient by ID
bool PatientList::removePatient(int id) {
    if (head == nullptr) return false;
    
    if (head->getId() == id) {
        Patient* temp = head;
        head = head->getNext();
        delete temp;
        count--;
        return true;
    }
    
    Patient* current = head;
    while (current->getNext() != nullptr) {
        if (current->getNext()->getId() == id) {
            Patient* temp = current->getNext();
            current->setNext(temp->getNext());
            delete temp;
            count--;
            return true;
        }
        current = current->getNext();
    }
    return false;
}

// Find patient by ID
Patient* PatientList::findPatient(int id) const {
    Patient* current = head;
    while (current != nullptr) {
        if (current->getId() == id) {
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}

// Find patient by name
Patient* PatientList::findPatientByName(const std::string& name) const {
    Patient* current = head;
    while (current != nullptr) {
        if (current->getName() == name) {
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}

// Display all patients
void PatientList::displayAll() const {
    if (head == nullptr) {
        std::cout << "No patients found." << std::endl;
        return;
    }
    
    Patient* current = head;
    int index = 1;
    while (current != nullptr) {
        std::cout << "\n--- Patient " << index << " ---" << std::endl;
        current->display();
        current = current->getNext();
        index++;
    }
}

// Display patients by disease
void PatientList::displayByDisease(const std::string& disease) const {
    Patient* current = head;
    bool found = false;
    int index = 1;
    
    while (current != nullptr) {
        if (current->getDisease() == disease) {
            std::cout << "\n--- Patient " << index << " ---" << std::endl;
            current->display();
            found = true;
            index++;
        }
        current = current->getNext();
    }
    
    if (!found) {
        std::cout << "No patients found with disease: " << disease << std::endl;
    }
}

// Get count
int PatientList::getCount() const {
    return count;
}

// Get next ID
int PatientList::getNextId() {
    return nextId++;
}

// Get head
Patient* PatientList::getHead() const {
    return head;
}

// Save to file
bool PatientList::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    file << nextId << std::endl; // Save next ID
    file << count << std::endl;  // Save count
    
    Patient* current = head;
    while (current != nullptr) {
        file << *current << std::endl;
        current = current->getNext();
    }
    
    file.close();
    return true;
}

// Load from file
bool PatientList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    clear(); // Clear existing data
    
    file >> nextId >> count;
    file.ignore(); // Ignore newline
    
    for (int i = 0; i < count; i++) {
        Patient patient;
        file >> patient;
        if (patient.isValid()) {
            Patient* newPatient = new Patient(patient);
            if (head == nullptr) {
                head = newPatient;
            } else {
                Patient* current = head;
                while (current->getNext() != nullptr) {
                    current = current->getNext();
                }
                current->setNext(newPatient);
            }
        }
    }
    
    file.close();
    return true;
}

// Check if empty
bool PatientList::isEmpty() const {
    return head == nullptr;
}

// Clear all patients
void PatientList::clear() {
    while (head != nullptr) {
        Patient* temp = head;
        head = head->getNext();
        delete temp;
    }
    count = 0;
    nextId = 1;
}

// Search patients
std::vector<Patient*> PatientList::searchPatients(const std::string& searchTerm) const {
    std::vector<Patient*> results;
    Patient* current = head;
    
    while (current != nullptr) {
        std::string name = current->getName();
        std::string disease = current->getDisease();
        std::string contact = current->getContactInfo();
        
        // Convert to lowercase for case-insensitive search
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        std::transform(disease.begin(), disease.end(), disease.begin(), ::tolower);
        std::transform(contact.begin(), contact.end(), contact.begin(), ::tolower);
        std::string searchLower = searchTerm;
        std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);
        
        if (name.find(searchLower) != std::string::npos ||
            disease.find(searchLower) != std::string::npos ||
            contact.find(searchLower) != std::string::npos) {
            results.push_back(current);
        }
        current = current->getNext();
    }
    
    return results;
}

// Copy constructor
PatientList::PatientList(const PatientList& other) : head(nullptr), count(0), nextId(other.nextId) {
    Patient* current = other.head;
    while (current != nullptr) {
        addPatient(*current);
        current = current->getNext();
    }
}

// Assignment operator
PatientList& PatientList::operator=(const PatientList& other) {
    if (this != &other) {
        clear();
        nextId = other.nextId;
        Patient* current = other.head;
        while (current != nullptr) {
            addPatient(*current);
            current = current->getNext();
        }
    }
    return *this;
}