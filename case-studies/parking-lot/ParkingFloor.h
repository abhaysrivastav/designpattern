#pragma once
#include <vector>
#include <memory>
#include <map>
#include "ParkingSpot.h"
#include "DisplayBoard.h"
#include "Vehicle.h"

class ParkingFloor {
private:
    int floorNumber;
    std::vector<std::shared_ptr<ParkingSpot>> spots;
    std::map<ParkingSpotType, std::vector<std::shared_ptr<ParkingSpot>>> spotsByType;
    DisplayBoard displayBoard;

public:
    ParkingFloor(int number) : floorNumber(number), displayBoard(number) {}

    void addSpot(std::shared_ptr<ParkingSpot> spot) {
        spots.push_back(spot);
        spotsByType[spot->getType()].push_back(spot);
        displayBoard.incrementAvailability(spot->getType());
    }

    int getFloorNumber() const { return floorNumber; }

    DisplayBoard& getDisplayBoard() { return displayBoard; }

    // Find an available spot for the vehicle
    std::shared_ptr<ParkingSpot> findAvailableSpot(std::shared_ptr<Vehicle> vehicle) {
        VehicleType vType = vehicle->getType();
        
        // Priority order for spot selection based on vehicle type
        std::vector<ParkingSpotType> preferredSpots;
        
        switch (vType) {
            case VehicleType::MOTORCYCLE:
                // Prefer motorcycle spots, then compact, then others
                preferredSpots = {ParkingSpotType::MOTORCYCLE, ParkingSpotType::COMPACT, 
                                 ParkingSpotType::ACCESSIBLE, ParkingSpotType::LARGE};
                break;
            case VehicleType::CAR:
                // Prefer compact, then accessible, then large
                preferredSpots = {ParkingSpotType::COMPACT, ParkingSpotType::ACCESSIBLE, 
                                 ParkingSpotType::LARGE};
                break;
            case VehicleType::VAN:
                // Prefer accessible, then large
                preferredSpots = {ParkingSpotType::ACCESSIBLE, ParkingSpotType::LARGE};
                break;
            case VehicleType::TRUCK:
                // Only large spots
                preferredSpots = {ParkingSpotType::LARGE};
                break;
        }

        // Try to find spot in order of preference
        for (ParkingSpotType spotType : preferredSpots) {
            auto& typeSpots = spotsByType[spotType];
            for (auto& spot : typeSpots) {
                if (spot->isAvailable() && spot->canFitVehicle(vehicle)) {
                    return spot;
                }
            }
        }

        return nullptr; // No available spot found
    }

    bool assignSpot(std::shared_ptr<ParkingSpot> spot, std::shared_ptr<Vehicle> vehicle) {
        if (spot->assignVehicle(vehicle)) {
            displayBoard.decrementAvailability(spot->getType());
            return true;
        }
        return false;
    }

    void releaseSpot(std::shared_ptr<ParkingSpot> spot) {
        ParkingSpotType type = spot->getType();
        spot->removeVehicle();
        displayBoard.incrementAvailability(type);
    }

    int getTotalSpots() const {
        return spots.size();
    }

    int getAvailableSpots() const {
        int count = 0;
        for (const auto& spot : spots) {
            if (spot->isAvailable()) count++;
        }
        return count;
    }
};
