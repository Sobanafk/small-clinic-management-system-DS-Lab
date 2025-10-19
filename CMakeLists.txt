cmake_minimum_required(VERSION 3.10)
project(ClinicManagementSystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()

# Find SFML (optional for GUI)
find_package(SFML 2.5 COMPONENTS graphics window system)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Source files
set(SOURCES
    main.cpp
    Patient.cpp
    Doctor.cpp
    Appointment.cpp
    PatientList.cpp
    DoctorList.cpp
    AppointmentQueue.cpp
    Clinic.cpp
    MenuSystem.cpp
)

# Header files
set(HEADERS
    Patient.h
    Doctor.h
    Appointment.h
    PatientList.h
    DoctorList.h
    AppointmentQueue.h
    Clinic.h
    MenuSystem.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link SFML if available (for future GUI implementation)
if(SFML_FOUND)
    target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SFML_AVAILABLE)
    message(STATUS "SFML found - GUI features will be available")
else()
    message(STATUS "SFML not found - Console mode only")
endif()

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Create data directory
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/data)

# Copy sample data files to build directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/patients.txt ${CMAKE_BINARY_DIR}/data/patients.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/doctors.txt ${CMAKE_BINARY_DIR}/data/doctors.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/appointments.txt ${CMAKE_BINARY_DIR}/data/appointments.txt COPYONLY)

# Installation rules
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY data/ DESTINATION data)

# Print configuration summary
message(STATUS "Configuration Summary:")
message(STATUS "  Project: ${PROJECT_NAME}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  SFML Available: ${SFML_FOUND}")