#pragma once
#include <string>

enum class VehicleType {
    CAR,
    TRUCK,
    VAN,
    MOTORCYCLE
};

class Vehicle {
protected:
    std::string licenseNumber;
    VehicleType type;

public:
    Vehicle(const std::string& license, VehicleType vType)
        : licenseNumber(license), type(vType) {}

    virtual ~Vehicle() = default;

    std::string getLicenseNumber() const { return licenseNumber; }
    
    VehicleType getType() const { return type; }

    virtual std::string getTypeName() const = 0;
};

class Car : public Vehicle {
public:
    Car(const std::string& license)
        : Vehicle(license, VehicleType::CAR) {}

    std::string getTypeName() const override { return "Car"; }
};

class Truck : public Vehicle {
public:
    Truck(const std::string& license)
        : Vehicle(license, VehicleType::TRUCK) {}

    std::string getTypeName() const override { return "Truck"; }
};

class Van : public Vehicle {
public:
    Van(const std::string& license)
        : Vehicle(license, VehicleType::VAN) {}

    std::string getTypeName() const override { return "Van"; }
};

class Motorcycle : public Vehicle {
public:
    Motorcycle(const std::string& license)
        : Vehicle(license, VehicleType::MOTORCYCLE) {}

    std::string getTypeName() const override { return "Motorcycle"; }
};
