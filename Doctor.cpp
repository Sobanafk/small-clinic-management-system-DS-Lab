#include "Doctor.h"
#include <sstream>
#include <vector>

// Default constructor
Doctor::Doctor() : id(0), name(""), specialization(""), contactInfo(""), schedule(""), isAvailable(true), next(nullptr) {}

// Parameterized constructor
Doctor::Doctor(int id, const std::string& name, const std::string& specialization, 
               const std::string& contactInfo, const std::string& schedule, bool isAvailable)
    : id(id), name(name), specialization(specialization), contactInfo(contactInfo), 
      schedule(schedule), isAvailable(isAvailable), next(nullptr) {}

// Getters
int Doctor::getId() const { return id; }
std::string Doctor::getName() const { return name; }
std::string Doctor::getSpecialization() const { return specialization; }
std::string Doctor::getContactInfo() const { return contactInfo; }
std::string Doctor::getSchedule() const { return schedule; }
bool Doctor::getIsAvailable() const { return isAvailable; }
Doctor* Doctor::getNext() const { return next; }

// Setters
void Doctor::setId(int id) { this->id = id; }
void Doctor::setName(const std::string& name) { this->name = name; }
void Doctor::setSpecialization(const std::string& specialization) { this->specialization = specialization; }
void Doctor::setContactInfo(const std::string& contactInfo) { this->contactInfo = contactInfo; }
void Doctor::setSchedule(const std::string& schedule) { this->schedule = schedule; }
void Doctor::setIsAvailable(bool isAvailable) { this->isAvailable = isAvailable; }
void Doctor::setNext(Doctor* next) { this->next = next; }

// Display doctor information
void Doctor::display() const {
    std::cout << "\n=== Doctor Information ===" << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Name: Dr. " << name << std::endl;
    std::cout << "Specialization: " << specialization << std::endl;
    std::cout << "Contact: " << contactInfo << std::endl;
    std::cout << "Schedule: " << schedule << std::endl;
    std::cout << "Available: " << (isAvailable ? "Yes" : "No") << std::endl;
    std::cout << "=========================" << std::endl;
}

// Convert doctor to string
std::string Doctor::toString() const {
    std::ostringstream oss;
    oss << id << "|" << name << "|" << specialization << "|" << contactInfo << "|" << schedule << "|" << (isAvailable ? "1" : "0");
    return oss.str();
}

// Validate doctor data
bool Doctor::isValid() const {
    return id > 0 && !name.empty() && !specialization.empty() && !contactInfo.empty();
}

// Toggle availability
void Doctor::toggleAvailability() {
    isAvailable = !isAvailable;
}

// Output operator for file writing
std::ostream& operator<<(std::ostream& os, const Doctor& doctor) {
    os << doctor.toString();
    return os;
}

// Input operator for file reading
std::istream& operator>>(std::istream& is, Doctor& doctor) {
    std::string line;
    if (std::getline(is, line)) {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;
        
        while (std::getline(iss, token, '|')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 6) {
            doctor.id = std::stoi(tokens[0]);
            doctor.name = tokens[1];
            doctor.specialization = tokens[2];
            doctor.contactInfo = tokens[3];
            doctor.schedule = tokens[4];
            doctor.isAvailable = (tokens[5] == "1");
        }
    }
    return is;
}