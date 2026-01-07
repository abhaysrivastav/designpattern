#pragma once
#include "Vehicle.h"
#include "ParkingSpot.h"
#include <cmath>

class PricingStrategy {
public:
    virtual ~PricingStrategy() = default;
    virtual double calculatePrice(double hours, VehicleType vType, ParkingSpotType spotType) = 0;
};

class HourlyPricingStrategy : public PricingStrategy {
private:
    double firstHourRate;
    double additionalHourRate;
    double largeSpotPremium;

public:
    HourlyPricingStrategy(double firstRate = 4.0, double additionalRate = 3.5, double premium = 1.0)
        : firstHourRate(firstRate), additionalHourRate(additionalRate), largeSpotPremium(premium) {}

    double calculatePrice(double hours, VehicleType vType, ParkingSpotType spotType) override {
        if (hours <= 0) return 0.0;

        // Round up to nearest hour
        int totalHours = static_cast<int>(std::ceil(hours));
        
        double price = 0.0;
        
        // First hour
        if (totalHours >= 1) {
            price += firstHourRate;
        }
        
        // Additional hours
        if (totalHours > 1) {
            price += (totalHours - 1) * additionalHourRate;
        }
        
        // Large spot premium
        if (spotType == ParkingSpotType::LARGE) {
            price += totalHours * largeSpotPremium;
        }
        
        // Vehicle type multiplier
        switch (vType) {
            case VehicleType::MOTORCYCLE:
                price *= 0.75; // 25% discount
                break;
            case VehicleType::TRUCK:
                price *= 1.25; // 25% surcharge
                break;
            case VehicleType::CAR:
            case VehicleType::VAN:
            default:
                // No adjustment
                break;
        }

        return price;
    }
};

// Lost ticket pricing - charge maximum daily rate
class LostTicketPricingStrategy : public PricingStrategy {
private:
    double maxDailyRate;

public:
    LostTicketPricingStrategy(double maxRate = 50.0)
        : maxDailyRate(maxRate) {}

    double calculatePrice(double hours, VehicleType vType, ParkingSpotType spotType) override {
        return maxDailyRate;
    }
};
