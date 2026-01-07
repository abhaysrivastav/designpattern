#include "ParkingSpot.h"
#include "Vehicle.h"

// CompactSpot can fit: Motorcycle, Car
bool CompactSpot::canFitVehicle(std::shared_ptr<Vehicle> vehicle) {
    VehicleType vType = vehicle->getType();
    return (vType == VehicleType::MOTORCYCLE || vType == VehicleType::CAR);
}

// LargeSpot can fit: Motorcycle, Car, Van, Truck (all vehicles)
bool LargeSpot::canFitVehicle(std::shared_ptr<Vehicle> vehicle) {
    return true; // Can fit any vehicle
}

// MotorcycleSpot can only fit: Motorcycle
bool MotorcycleSpot::canFitVehicle(std::shared_ptr<Vehicle> vehicle) {
    return (vehicle->getType() == VehicleType::MOTORCYCLE);
}

// AccessibleSpot can fit: Motorcycle, Car, Van (not Truck for safety)
bool AccessibleSpot::canFitVehicle(std::shared_ptr<Vehicle> vehicle) {
    VehicleType vType = vehicle->getType();
    return (vType == VehicleType::MOTORCYCLE || 
            vType == VehicleType::CAR || 
            vType == VehicleType::VAN);
}
