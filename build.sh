#!/bin/bash

# Build script for Clinic Management System

echo "Building Clinic Management System..."

# Create build directory
mkdir -p build
cd build

# Configure with CMake
echo "Configuring with CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build the project
echo "Building project..."
make -j$(nproc)

# Check if build was successful
if [ $? -eq 0 ]; then
    echo "Build successful!"
    echo ""
    echo "Executables created:"
    echo "  Console version: ./bin/ClinicManagementSystem"
    if [ -f "./bin/ClinicManagementSystemGUI" ]; then
        echo "  GUI version: ./bin/ClinicManagementSystemGUI"
    fi
    echo ""
    echo "To run:"
    echo "  cd build && ./bin/ClinicManagementSystem"
else
    echo "Build failed!"
    exit 1
fi