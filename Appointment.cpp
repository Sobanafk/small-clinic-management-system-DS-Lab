#include "Appointment.h"
#include <sstream>
#include <vector>

// Default constructor
Appointment::Appointment() : appointmentId(0), patientId(0), doctorId(0), 
                             patientName(""), doctorName(""), date(""), time(""), 
                             status("Scheduled"), notes(""), next(nullptr) {}

// Parameterized constructor
Appointment::Appointment(int appointmentId, int patientId, int doctorId, 
                         const std::string& patientName, const std::string& doctorName,
                         const std::string& date, const std::string& time, 
                         const std::string& status, const std::string& notes)
    : appointmentId(appointmentId), patientId(patientId), doctorId(doctorId),
      patientName(patientName), doctorName(doctorName), date(date), time(time),
      status(status), notes(notes), next(nullptr) {}

// Getters
int Appointment::getAppointmentId() const { return appointmentId; }
int Appointment::getPatientId() const { return patientId; }
int Appointment::getDoctorId() const { return doctorId; }
std::string Appointment::getPatientName() const { return patientName; }
std::string Appointment::getDoctorName() const { return doctorName; }
std::string Appointment::getDate() const { return date; }
std::string Appointment::getTime() const { return time; }
std::string Appointment::getStatus() const { return status; }
std::string Appointment::getNotes() const { return notes; }
Appointment* Appointment::getNext() const { return next; }

// Setters
void Appointment::setAppointmentId(int appointmentId) { this->appointmentId = appointmentId; }
void Appointment::setPatientId(int patientId) { this->patientId = patientId; }
void Appointment::setDoctorId(int doctorId) { this->doctorId = doctorId; }
void Appointment::setPatientName(const std::string& patientName) { this->patientName = patientName; }
void Appointment::setDoctorName(const std::string& doctorName) { this->doctorName = doctorName; }
void Appointment::setDate(const std::string& date) { this->date = date; }
void Appointment::setTime(const std::string& time) { this->time = time; }
void Appointment::setStatus(const std::string& status) { this->status = status; }
void Appointment::setNotes(const std::string& notes) { this->notes = notes; }
void Appointment::setNext(Appointment* next) { this->next = next; }

// Display appointment information
void Appointment::display() const {
    std::cout << "\n=== Appointment Information ===" << std::endl;
    std::cout << "Appointment ID: " << appointmentId << std::endl;
    std::cout << "Patient: " << patientName << " (ID: " << patientId << ")" << std::endl;
    std::cout << "Doctor: Dr. " << doctorName << " (ID: " << doctorId << ")" << std::endl;
    std::cout << "Date: " << date << std::endl;
    std::cout << "Time: " << time << std::endl;
    std::cout << "Status: " << status << std::endl;
    if (!notes.empty()) {
        std::cout << "Notes: " << notes << std::endl;
    }
    std::cout << "===============================" << std::endl;
}

// Convert appointment to string
std::string Appointment::toString() const {
    std::ostringstream oss;
    oss << appointmentId << "|" << patientId << "|" << doctorId << "|" 
        << patientName << "|" << doctorName << "|" << date << "|" << time << "|" 
        << status << "|" << notes;
    return oss.str();
}

// Validate appointment data
bool Appointment::isValid() const {
    return appointmentId > 0 && patientId > 0 && doctorId > 0 && 
           !patientName.empty() && !doctorName.empty() && 
           !date.empty() && !time.empty();
}

// Cancel appointment
void Appointment::cancel() {
    status = "Cancelled";
}

// Complete appointment
void Appointment::complete() {
    status = "Completed";
}

// Output operator for file writing
std::ostream& operator<<(std::ostream& os, const Appointment& appointment) {
    os << appointment.toString();
    return os;
}

// Input operator for file reading
std::istream& operator>>(std::istream& is, Appointment& appointment) {
    std::string line;
    if (std::getline(is, line)) {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;
        
        while (std::getline(iss, token, '|')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 9) {
            appointment.appointmentId = std::stoi(tokens[0]);
            appointment.patientId = std::stoi(tokens[1]);
            appointment.doctorId = std::stoi(tokens[2]);
            appointment.patientName = tokens[3];
            appointment.doctorName = tokens[4];
            appointment.date = tokens[5];
            appointment.time = tokens[6];
            appointment.status = tokens[7];
            appointment.notes = tokens[8];
        }
    }
    return is;
}