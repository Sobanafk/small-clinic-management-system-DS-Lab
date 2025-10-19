# Small Clinic Management System (C++)

A comprehensive C++ application designed to automate and manage the operations of a small medical clinic. The system enables users to handle patient records, doctor information, and appointment scheduling efficiently using advanced data structures and file management.

## 🎯 Features

### Core Functionality
- **Patient Management**: Add, update, search, and delete patient records
- **Doctor Management**: Manage doctor information, specializations, and availability
- **Appointment Scheduling**: Book, cancel, and track appointments using queue data structure
- **Data Persistence**: Automatic saving and loading of all data using text files
- **Search & Filter**: Advanced search capabilities across all entities
- **Statistics & Reports**: Comprehensive reporting and analytics

### Data Structures Used
- **Linked Lists**: For managing patient and doctor records
- **Queues**: For appointment scheduling (first-come, first-served)
- **Stacks**: For operation history and undo functionality
- **File I/O**: For persistent data storage

### User Interfaces
- **Console Interface**: Full-featured command-line interface
- **GUI Interface**: Modern graphical interface using SFML (optional)

## 🏗️ System Architecture

### Core Classes
- `Patient`: Stores patient information (ID, name, age, disease, contact, address)
- `Doctor`: Manages doctor details (ID, name, specialization, schedule, availability)
- `Appointment`: Handles appointment data (ID, patient, doctor, date, time, status)
- `Clinic`: Main controller class managing all operations
- `MenuSystem`: Console-based user interface
- `GUI`: SFML-based graphical interface

### Data Management
- `PatientList`: Linked list implementation for patient records
- `DoctorList`: Linked list implementation for doctor records
- `AppointmentQueue`: Queue implementation for appointment scheduling

## 🚀 Getting Started

### Prerequisites
- C++17 compatible compiler (GCC, Clang, MSVC)
- CMake 3.10 or higher
- SFML 2.5+ (optional, for GUI features)

### Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/small-clinic-management-system.git
   cd small-clinic-management-system
   ```

2. **Build the project:**
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

3. **Run the application:**
   ```bash
   # Console version
   ./bin/ClinicManagementSystem
   
   # GUI version (if SFML is available)
   ./bin/ClinicManagementSystemGUI
   ```

### Alternative Build Methods

**Using Code::Blocks:**
1. Open the project in Code::Blocks
2. Build and run

**Using Visual Studio:**
1. Open the project folder in Visual Studio
2. Build and run

## 📁 Project Structure

```
clinic-management-system/
├── src/
│   ├── Patient.h/cpp          # Patient class implementation
│   ├── Doctor.h/cpp           # Doctor class implementation
│   ├── Appointment.h/cpp      # Appointment class implementation
│   ├── PatientList.h/cpp      # Patient linked list
│   ├── DoctorList.h/cpp       # Doctor linked list
│   ├── AppointmentQueue.h/cpp # Appointment queue
│   ├── Clinic.h/cpp           # Main clinic controller
│   ├── MenuSystem.h/cpp       # Console interface
│   ├── GUI.h/cpp              # SFML GUI interface
│   ├── main.cpp               # Console main
│   └── main_gui.cpp           # GUI main
├── data/
│   ├── patients.txt           # Patient data storage
│   ├── doctors.txt            # Doctor data storage
│   └── appointments.txt       # Appointment data storage
├── CMakeLists.txt             # Build configuration
└── README.md                  # This file
```

## 💻 Usage

### Console Interface
The console interface provides a menu-driven system with the following options:

1. **Patient Management**
   - Add new patients
   - Update patient information
   - Search patients
   - View all patients
   - Remove patients

2. **Doctor Management**
   - Add new doctors
   - Update doctor information
   - Search doctors
   - View all doctors
   - Toggle doctor availability

3. **Appointment Management**
   - Book new appointments
   - Cancel appointments
   - Complete appointments
   - View appointments by various criteria

4. **Reports & Statistics**
   - System statistics
   - Patient history
   - Doctor schedules

### GUI Interface
The graphical interface provides an intuitive point-and-click interface with:
- Visual forms for data entry
- List views for browsing records
- Interactive buttons and menus
- Real-time data display

## 🔧 Configuration

### File Storage
Data is automatically saved to text files in the `data/` directory:
- `patients.txt`: Patient records
- `doctors.txt`: Doctor records
- `appointments.txt`: Appointment records

### Customization
You can modify file paths in the `Clinic` constructor:
```cpp
Clinic clinic("custom_patients.txt", "custom_doctors.txt", "custom_appointments.txt");
```

## 🧪 Testing

The system includes comprehensive error handling and input validation:
- Date format validation (DD/MM/YYYY)
- Time format validation (HH:MM)
- Age range validation (1-150)
- Required field validation
- Duplicate prevention

## 📊 Sample Data

The system comes with sample data including:
- 3 sample patients with various conditions
- 3 sample doctors with different specializations
- 2 sample appointments

## 🛠️ Development

### Adding New Features
1. Extend the appropriate class (Patient, Doctor, Appointment)
2. Update the Clinic class for new operations
3. Add menu options in MenuSystem or GUI
4. Update file I/O methods if needed

### Code Style
- Follow C++17 standards
- Use meaningful variable names
- Include comprehensive comments
- Implement proper error handling

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests if applicable
5. Submit a pull request

## 📝 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 🆘 Support

For support and questions:
- Create an issue in the repository
- Check the documentation
- Review the code comments

## 🔮 Future Enhancements

- Database integration (SQLite/MySQL)
- Web-based interface
- Mobile app support
- Advanced reporting features
- Multi-clinic support
- Integration with medical devices
