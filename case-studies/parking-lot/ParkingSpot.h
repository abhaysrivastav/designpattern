#pragma once
#include <string>
#include <memory>

enum class ParkingSpotType {
    COMPACT,
    LARGE,
    MOTORCYCLE,
    ACCESSIBLE
};

// Forward declaration
class Vehicle;

class ParkingSpot {
protected:
    std::string spotId;
    ParkingSpotType type;
    bool isFree;
    std::shared_ptr<Vehicle> currentVehicle;
    int floorNumber;

public:
    ParkingSpot(const std::string& id, ParkingSpotType spotType, int floor)
        : spotId(id), type(spotType), isFree(true), currentVehicle(nullptr), floorNumber(floor) {}

    virtual ~ParkingSpot() = default;

    bool isAvailable() const { return isFree; }
    
    ParkingSpotType getType() const { return type; }
    
    std::string getSpotId() const { return spotId; }
    
    int getFloorNumber() const { return floorNumber; }

    virtual bool canFitVehicle(std::shared_ptr<Vehicle> vehicle) = 0;

    bool assignVehicle(std::shared_ptr<Vehicle> vehicle) {
        if (!isFree || !canFitVehicle(vehicle)) {
            return false;
        }
        currentVehicle = vehicle;
        isFree = false;
        return true;
    }

    void removeVehicle() {
        currentVehicle = nullptr;
        isFree = true;
    }

    std::shared_ptr<Vehicle> getVehicle() const {
        return currentVehicle;
    }
};

class CompactSpot : public ParkingSpot {
public:
    CompactSpot(const std::string& id, int floor)
        : ParkingSpot(id, ParkingSpotType::COMPACT, floor) {}

    bool canFitVehicle(std::shared_ptr<Vehicle> vehicle) override;
};

class LargeSpot : public ParkingSpot {
public:
    LargeSpot(const std::string& id, int floor)
        : ParkingSpot(id, ParkingSpotType::LARGE, floor) {}

    bool canFitVehicle(std::shared_ptr<Vehicle> vehicle) override;
};

class MotorcycleSpot : public ParkingSpot {
public:
    MotorcycleSpot(const std::string& id, int floor)
        : ParkingSpot(id, ParkingSpotType::MOTORCYCLE, floor) {}

    bool canFitVehicle(std::shared_ptr<Vehicle> vehicle) override;
};

class AccessibleSpot : public ParkingSpot {
public:
    AccessibleSpot(const std::string& id, int floor)
        : ParkingSpot(id, ParkingSpotType::ACCESSIBLE, floor) {}

    bool canFitVehicle(std::shared_ptr<Vehicle> vehicle) override;
};
