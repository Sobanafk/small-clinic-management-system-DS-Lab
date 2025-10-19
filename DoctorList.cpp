#include "DoctorList.h"
#include <iostream>
#include <algorithm>
#include <vector>

// Constructor
DoctorList::DoctorList() : head(nullptr), count(0), nextId(1) {}

// Destructor
DoctorList::~DoctorList() {
    clear();
}

// Add doctor to the list
void DoctorList::addDoctor(const Doctor& doctor) {
    Doctor* newDoctor = new Doctor(doctor);
    newDoctor->setId(nextId++);
    
    if (head == nullptr) {
        head = newDoctor;
    } else {
        Doctor* current = head;
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        current->setNext(newDoctor);
    }
    count++;
}

// Remove doctor by ID
bool DoctorList::removeDoctor(int id) {
    if (head == nullptr) return false;
    
    if (head->getId() == id) {
        Doctor* temp = head;
        head = head->getNext();
        delete temp;
        count--;
        return true;
    }
    
    Doctor* current = head;
    while (current->getNext() != nullptr) {
        if (current->getNext()->getId() == id) {
            Doctor* temp = current->getNext();
            current->setNext(temp->getNext());
            delete temp;
            count--;
            return true;
        }
        current = current->getNext();
    }
    return false;
}

// Find doctor by ID
Doctor* DoctorList::findDoctor(int id) const {
    Doctor* current = head;
    while (current != nullptr) {
        if (current->getId() == id) {
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}

// Find doctor by name
Doctor* DoctorList::findDoctorByName(const std::string& name) const {
    Doctor* current = head;
    while (current != nullptr) {
        if (current->getName() == name) {
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}

// Display all doctors
void DoctorList::displayAll() const {
    if (head == nullptr) {
        std::cout << "No doctors found." << std::endl;
        return;
    }
    
    Doctor* current = head;
    int index = 1;
    while (current != nullptr) {
        std::cout << "\n--- Doctor " << index << " ---" << std::endl;
        current->display();
        current = current->getNext();
        index++;
    }
}

// Display doctors by specialization
void DoctorList::displayBySpecialization(const std::string& specialization) const {
    Doctor* current = head;
    bool found = false;
    int index = 1;
    
    while (current != nullptr) {
        if (current->getSpecialization() == specialization) {
            std::cout << "\n--- Doctor " << index << " ---" << std::endl;
            current->display();
            found = true;
            index++;
        }
        current = current->getNext();
    }
    
    if (!found) {
        std::cout << "No doctors found with specialization: " << specialization << std::endl;
    }
}

// Display available doctors
void DoctorList::displayAvailable() const {
    Doctor* current = head;
    bool found = false;
    int index = 1;
    
    while (current != nullptr) {
        if (current->getIsAvailable()) {
            std::cout << "\n--- Available Doctor " << index << " ---" << std::endl;
            current->display();
            found = true;
            index++;
        }
        current = current->getNext();
    }
    
    if (!found) {
        std::cout << "No available doctors found." << std::endl;
    }
}

// Get count
int DoctorList::getCount() const {
    return count;
}

// Get next ID
int DoctorList::getNextId() {
    return nextId++;
}

// Get head
Doctor* DoctorList::getHead() const {
    return head;
}

// Save to file
bool DoctorList::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    file << nextId << std::endl; // Save next ID
    file << count << std::endl;  // Save count
    
    Doctor* current = head;
    while (current != nullptr) {
        file << *current << std::endl;
        current = current->getNext();
    }
    
    file.close();
    return true;
}

// Load from file
bool DoctorList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    clear(); // Clear existing data
    
    file >> nextId >> count;
    file.ignore(); // Ignore newline
    
    for (int i = 0; i < count; i++) {
        Doctor doctor;
        file >> doctor;
        if (doctor.isValid()) {
            Doctor* newDoctor = new Doctor(doctor);
            if (head == nullptr) {
                head = newDoctor;
            } else {
                Doctor* current = head;
                while (current->getNext() != nullptr) {
                    current = current->getNext();
                }
                current->setNext(newDoctor);
            }
        }
    }
    
    file.close();
    return true;
}

// Check if empty
bool DoctorList::isEmpty() const {
    return head == nullptr;
}

// Clear all doctors
void DoctorList::clear() {
    while (head != nullptr) {
        Doctor* temp = head;
        head = head->getNext();
        delete temp;
    }
    count = 0;
    nextId = 1;
}

// Search doctors
std::vector<Doctor*> DoctorList::searchDoctors(const std::string& searchTerm) const {
    std::vector<Doctor*> results;
    Doctor* current = head;
    
    while (current != nullptr) {
        std::string name = current->getName();
        std::string specialization = current->getSpecialization();
        std::string contact = current->getContactInfo();
        
        // Convert to lowercase for case-insensitive search
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        std::transform(specialization.begin(), specialization.end(), specialization.begin(), ::tolower);
        std::transform(contact.begin(), contact.end(), contact.begin(), ::tolower);
        std::string searchLower = searchTerm;
        std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);
        
        if (name.find(searchLower) != std::string::npos ||
            specialization.find(searchLower) != std::string::npos ||
            contact.find(searchLower) != std::string::npos) {
            results.push_back(current);
        }
        current = current->getNext();
    }
    
    return results;
}

// Get available doctors
std::vector<Doctor*> DoctorList::getAvailableDoctors() const {
    std::vector<Doctor*> available;
    Doctor* current = head;
    
    while (current != nullptr) {
        if (current->getIsAvailable()) {
            available.push_back(current);
        }
        current = current->getNext();
    }
    
    return available;
}

// Copy constructor
DoctorList::DoctorList(const DoctorList& other) : head(nullptr), count(0), nextId(other.nextId) {
    Doctor* current = other.head;
    while (current != nullptr) {
        addDoctor(*current);
        current = current->getNext();
    }
}

// Assignment operator
DoctorList& DoctorList::operator=(const DoctorList& other) {
    if (this != &other) {
        clear();
        nextId = other.nextId;
        Doctor* current = other.head;
        while (current != nullptr) {
            addDoctor(*current);
            current = current->getNext();
        }
    }
    return *this;
}