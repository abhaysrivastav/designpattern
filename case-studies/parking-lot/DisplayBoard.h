#pragma once
#include <map>
#include <string>
#include "ParkingSpot.h"

class DisplayBoard {
private:
    int floorNumber;
    std::map<ParkingSpotType, int> availableSpots;

public:
    DisplayBoard(int floor) : floorNumber(floor) {
        availableSpots[ParkingSpotType::COMPACT] = 0;
        availableSpots[ParkingSpotType::LARGE] = 0;
        availableSpots[ParkingSpotType::MOTORCYCLE] = 0;
        availableSpots[ParkingSpotType::ACCESSIBLE] = 0;
    }

    void updateAvailability(ParkingSpotType type, int count) {
        availableSpots[type] = count;
    }

    void incrementAvailability(ParkingSpotType type) {
        availableSpots[type]++;
    }

    void decrementAvailability(ParkingSpotType type) {
        if (availableSpots[type] > 0) {
            availableSpots[type]--;
        }
    }

    int getAvailableSpots(ParkingSpotType type) const {
        auto it = availableSpots.find(type);
        return (it != availableSpots.end()) ? it->second : 0;
    }

    std::string getSpotTypeName(ParkingSpotType type) const {
        switch (type) {
            case ParkingSpotType::COMPACT: return "Compact";
            case ParkingSpotType::LARGE: return "Large";
            case ParkingSpotType::MOTORCYCLE: return "Motorcycle";
            case ParkingSpotType::ACCESSIBLE: return "Accessible";
            default: return "Unknown";
        }
    }

    void display() const {
        std::cout << "\n========== Floor " << floorNumber << " Display Board ==========\n";
        for (const auto& [type, count] : availableSpots) {
            std::cout << getSpotTypeName(type) << " Spots: " << count << " available\n";
        }
        std::cout << "==========================================\n";
    }

    bool isFull() const {
        for (const auto& [type, count] : availableSpots) {
            if (count > 0) return false;
        }
        return true;
    }
};
