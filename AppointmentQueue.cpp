#include "AppointmentQueue.h"
#include <iostream>
#include <algorithm>
#include <vector>

// Constructor
AppointmentQueue::AppointmentQueue() : front(nullptr), rear(nullptr), count(0), nextId(1) {}

// Destructor
AppointmentQueue::~AppointmentQueue() {
    clear();
}

// Enqueue appointment
void AppointmentQueue::enqueue(const Appointment& appointment) {
    Appointment* newAppointment = new Appointment(appointment);
    newAppointment->setAppointmentId(nextId++);
    
    if (rear == nullptr) {
        front = rear = newAppointment;
    } else {
        rear->setNext(newAppointment);
        rear = newAppointment;
    }
    count++;
}

// Dequeue appointment
bool AppointmentQueue::dequeue() {
    if (front == nullptr) return false;
    
    Appointment* temp = front;
    front = front->getNext();
    
    if (front == nullptr) {
        rear = nullptr;
    }
    
    delete temp;
    count--;
    return true;
}

// Peek at front appointment
Appointment* AppointmentQueue::peek() const {
    return front;
}

// Check if queue is empty
bool AppointmentQueue::isEmpty() const {
    return front == nullptr;
}

// Get queue size
int AppointmentQueue::size() const {
    return count;
}

// Cancel appointment by ID
bool AppointmentQueue::cancelAppointment(int appointmentId) {
    Appointment* current = front;
    while (current != nullptr) {
        if (current->getAppointmentId() == appointmentId) {
            current->cancel();
            return true;
        }
        current = current->getNext();
    }
    return false;
}

// Complete appointment by ID
bool AppointmentQueue::completeAppointment(int appointmentId) {
    Appointment* current = front;
    while (current != nullptr) {
        if (current->getAppointmentId() == appointmentId) {
            current->complete();
            return true;
        }
        current = current->getNext();
    }
    return false;
}

// Find appointment by ID
Appointment* AppointmentQueue::findAppointment(int appointmentId) const {
    Appointment* current = front;
    while (current != nullptr) {
        if (current->getAppointmentId() == appointmentId) {
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}

// Display all appointments
void AppointmentQueue::displayAll() const {
    if (front == nullptr) {
        std::cout << "No appointments found." << std::endl;
        return;
    }
    
    Appointment* current = front;
    int index = 1;
    while (current != nullptr) {
        std::cout << "\n--- Appointment " << index << " ---" << std::endl;
        current->display();
        current = current->getNext();
        index++;
    }
}

// Display appointments by patient ID
void AppointmentQueue::displayByPatient(int patientId) const {
    Appointment* current = front;
    bool found = false;
    int index = 1;
    
    while (current != nullptr) {
        if (current->getPatientId() == patientId) {
            std::cout << "\n--- Patient Appointment " << index << " ---" << std::endl;
            current->display();
            found = true;
            index++;
        }
        current = current->getNext();
    }
    
    if (!found) {
        std::cout << "No appointments found for patient ID: " << patientId << std::endl;
    }
}

// Display appointments by doctor ID
void AppointmentQueue::displayByDoctor(int doctorId) const {
    Appointment* current = front;
    bool found = false;
    int index = 1;
    
    while (current != nullptr) {
        if (current->getDoctorId() == doctorId) {
            std::cout << "\n--- Doctor Appointment " << index << " ---" << std::endl;
            current->display();
            found = true;
            index++;
        }
        current = current->getNext();
    }
    
    if (!found) {
        std::cout << "No appointments found for doctor ID: " << doctorId << std::endl;
    }
}

// Display appointments by status
void AppointmentQueue::displayByStatus(const std::string& status) const {
    Appointment* current = front;
    bool found = false;
    int index = 1;
    
    while (current != nullptr) {
        if (current->getStatus() == status) {
            std::cout << "\n--- " << status << " Appointment " << index << " ---" << std::endl;
            current->display();
            found = true;
            index++;
        }
        current = current->getNext();
    }
    
    if (!found) {
        std::cout << "No appointments found with status: " << status << std::endl;
    }
}

// Get next ID
int AppointmentQueue::getNextId() {
    return nextId++;
}

// Get front appointment
Appointment* AppointmentQueue::getFront() const {
    return front;
}

// Save to file
bool AppointmentQueue::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    file << nextId << std::endl; // Save next ID
    file << count << std::endl;  // Save count
    
    Appointment* current = front;
    while (current != nullptr) {
        file << *current << std::endl;
        current = current->getNext();
    }
    
    file.close();
    return true;
}

// Load from file
bool AppointmentQueue::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    clear(); // Clear existing data
    
    file >> nextId >> count;
    file.ignore(); // Ignore newline
    
    for (int i = 0; i < count; i++) {
        Appointment appointment;
        file >> appointment;
        if (appointment.isValid()) {
            enqueue(appointment);
        }
    }
    
    file.close();
    return true;
}

// Clear all appointments
void AppointmentQueue::clear() {
    while (front != nullptr) {
        Appointment* temp = front;
        front = front->getNext();
        delete temp;
    }
    rear = nullptr;
    count = 0;
    nextId = 1;
}

// Search appointments
std::vector<Appointment*> AppointmentQueue::searchAppointments(const std::string& searchTerm) const {
    std::vector<Appointment*> results;
    Appointment* current = front;
    
    while (current != nullptr) {
        std::string patientName = current->getPatientName();
        std::string doctorName = current->getDoctorName();
        std::string date = current->getDate();
        std::string status = current->getStatus();
        
        // Convert to lowercase for case-insensitive search
        std::transform(patientName.begin(), patientName.end(), patientName.begin(), ::tolower);
        std::transform(doctorName.begin(), doctorName.end(), doctorName.begin(), ::tolower);
        std::transform(date.begin(), date.end(), date.begin(), ::tolower);
        std::transform(status.begin(), status.end(), status.begin(), ::tolower);
        std::string searchLower = searchTerm;
        std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);
        
        if (patientName.find(searchLower) != std::string::npos ||
            doctorName.find(searchLower) != std::string::npos ||
            date.find(searchLower) != std::string::npos ||
            status.find(searchLower) != std::string::npos) {
            results.push_back(current);
        }
        current = current->getNext();
    }
    
    return results;
}

// Get appointments by date
std::vector<Appointment*> AppointmentQueue::getAppointmentsByDate(const std::string& date) const {
    std::vector<Appointment*> results;
    Appointment* current = front;
    
    while (current != nullptr) {
        if (current->getDate() == date) {
            results.push_back(current);
        }
        current = current->getNext();
    }
    
    return results;
}

// Copy constructor
AppointmentQueue::AppointmentQueue(const AppointmentQueue& other) : front(nullptr), rear(nullptr), count(0), nextId(other.nextId) {
    Appointment* current = other.front;
    while (current != nullptr) {
        enqueue(*current);
        current = current->getNext();
    }
}

// Assignment operator
AppointmentQueue& AppointmentQueue::operator=(const AppointmentQueue& other) {
    if (this != &other) {
        clear();
        nextId = other.nextId;
        Appointment* current = other.front;
        while (current != nullptr) {
            enqueue(*current);
            current = current->getNext();
        }
    }
    return *this;
}