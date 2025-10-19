#include "Patient.h"
#include <sstream>
#include <vector>

// Default constructor
Patient::Patient() : id(0), name(""), age(0), disease(""), contactInfo(""), address(""), next(nullptr) {}

// Parameterized constructor
Patient::Patient(int id, const std::string& name, int age, const std::string& disease, 
                 const std::string& contactInfo, const std::string& address)
    : id(id), name(name), age(age), disease(disease), contactInfo(contactInfo), address(address), next(nullptr) {}

// Getters
int Patient::getId() const { return id; }
std::string Patient::getName() const { return name; }
int Patient::getAge() const { return age; }
std::string Patient::getDisease() const { return disease; }
std::string Patient::getContactInfo() const { return contactInfo; }
std::string Patient::getAddress() const { return address; }
Patient* Patient::getNext() const { return next; }

// Setters
void Patient::setId(int id) { this->id = id; }
void Patient::setName(const std::string& name) { this->name = name; }
void Patient::setAge(int age) { this->age = age; }
void Patient::setDisease(const std::string& disease) { this->disease = disease; }
void Patient::setContactInfo(const std::string& contactInfo) { this->contactInfo = contactInfo; }
void Patient::setAddress(const std::string& address) { this->address = address; }
void Patient::setNext(Patient* next) { this->next = next; }

// Display patient information
void Patient::display() const {
    std::cout << "\n=== Patient Information ===" << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Disease: " << disease << std::endl;
    std::cout << "Contact: " << contactInfo << std::endl;
    std::cout << "Address: " << address << std::endl;
    std::cout << "=========================" << std::endl;
}

// Convert patient to string
std::string Patient::toString() const {
    std::ostringstream oss;
    oss << id << "|" << name << "|" << age << "|" << disease << "|" << contactInfo << "|" << address;
    return oss.str();
}

// Validate patient data
bool Patient::isValid() const {
    return id > 0 && !name.empty() && age > 0 && age <= 150 && !contactInfo.empty();
}

// Output operator for file writing
std::ostream& operator<<(std::ostream& os, const Patient& patient) {
    os << patient.toString();
    return os;
}

// Input operator for file reading
std::istream& operator>>(std::istream& is, Patient& patient) {
    std::string line;
    if (std::getline(is, line)) {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;
        
        while (std::getline(iss, token, '|')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 6) {
            patient.id = std::stoi(tokens[0]);
            patient.name = tokens[1];
            patient.age = std::stoi(tokens[2]);
            patient.disease = tokens[3];
            patient.contactInfo = tokens[4];
            patient.address = tokens[5];
        }
    }
    return is;
}