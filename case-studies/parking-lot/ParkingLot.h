#pragma once
#include <vector>
#include <memory>
#include <map>
#include <mutex>
#include <iostream>
#include "ParkingFloor.h"
#include "ParkingTicket.h"
#include "PricingStrategy.h"
#include "Vehicle.h"
#include "Payment.h"

class ParkingLot {
private:
    static ParkingLot* instance;
    static std::mutex instanceMutex;

    std::string name;
    std::vector<std::shared_ptr<ParkingFloor>> floors;
    std::map<std::string, std::shared_ptr<ParkingTicket>> activeTickets;
    std::unique_ptr<PricingStrategy> pricingStrategy;
    std::mutex lotMutex;
    int maxCapacity;
    int currentOccupancy;

    // Private constructor for singleton
    ParkingLot(const std::string& lotName, int capacity = 40000)
        : name(lotName), maxCapacity(capacity), currentOccupancy(0) {
        pricingStrategy = std::make_unique<HourlyPricingStrategy>();
    }

public:
    // Singleton instance getter
    static ParkingLot* getInstance(const std::string& name = "Central Parking Lot") {
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(instanceMutex);
            if (instance == nullptr) {
                instance = new ParkingLot(name);
            }
        }
        return instance;
    }

    // Prevent copying
    ParkingLot(const ParkingLot&) = delete;
    ParkingLot& operator=(const ParkingLot&) = delete;

    void addFloor(std::shared_ptr<ParkingFloor> floor) {
        floors.push_back(floor);
    }

    bool isFull() const {
        return currentOccupancy >= maxCapacity;
    }

    // Entry point - issue ticket
    std::shared_ptr<ParkingTicket> issueTicket(std::shared_ptr<Vehicle> vehicle) {
        std::lock_guard<std::mutex> lock(lotMutex);

        if (isFull()) {
            std::cout << "❌ Parking lot is FULL! Cannot issue ticket.\n";
            return nullptr;
        }

        // Find available spot across all floors
        std::shared_ptr<ParkingSpot> availableSpot = nullptr;
        std::shared_ptr<ParkingFloor> selectedFloor = nullptr;

        for (auto& floor : floors) {
            availableSpot = floor->findAvailableSpot(vehicle);
            if (availableSpot) {
                selectedFloor = floor;
                break;
            }
        }

        if (!availableSpot) {
            std::cout << "❌ No suitable parking spot available for " 
                      << vehicle->getTypeName() << "\n";
            return nullptr;
        }

        // Assign the spot
        if (!selectedFloor->assignSpot(availableSpot, vehicle)) {
            std::cout << "❌ Failed to assign spot\n";
            return nullptr;
        }

        // Create ticket
        auto ticket = std::make_shared<ParkingTicket>(vehicle, availableSpot);
        activeTickets[ticket->getTicketNumber()] = ticket;
        currentOccupancy++;

        std::cout << "✅ Ticket issued: " << ticket->getTicketNumber()
                  << " | Vehicle: " << vehicle->getLicenseNumber()
                  << " | Spot: " << availableSpot->getSpotId()
                  << " | Floor: " << selectedFloor->getFloorNumber() << "\n";

        return ticket;
    }

    // Exit point - calculate payment
    double processExit(const std::string& ticketNumber) {
        std::lock_guard<std::mutex> lock(lotMutex);

        auto ticketIt = activeTickets.find(ticketNumber);
        if (ticketIt == activeTickets.end()) {
            std::cout << "❌ Invalid ticket number: " << ticketNumber << "\n";
            return -1.0;
        }

        auto ticket = ticketIt->second;
        ticket->setExitTime(std::chrono::system_clock::now());

        // Calculate price
        double hours = ticket->getParkingDurationInHours();
        auto vehicle = ticket->getVehicle();
        auto spot = ticket->getAssignedSpot();

        double price = 0.0;
        if (ticket->getStatus() == TicketStatus::LOST) {
            LostTicketPricingStrategy lostStrategy;
            price = lostStrategy.calculatePrice(hours, vehicle->getType(), spot->getType());
        } else {
            price = pricingStrategy->calculatePrice(hours, vehicle->getType(), spot->getType());
        }

        ticket->setAmountDue(price);

        std::cout << "\n💰 Exit Processing:\n"
                  << "   Ticket: " << ticketNumber << "\n"
                  << "   Duration: " << hours << " hours\n"
                  << "   Amount Due: $" << price << "\n";

        return price;
    }

    // Complete payment and release spot
    bool completePayment(const std::string& ticketNumber, std::shared_ptr<Payment> payment) {
        std::lock_guard<std::mutex> lock(lotMutex);

        auto ticketIt = activeTickets.find(ticketNumber);
        if (ticketIt == activeTickets.end()) {
            return false;
        }

        auto ticket = ticketIt->second;

        // Process payment
        if (!payment->processPayment()) {
            std::cout << "❌ Payment failed!\n";
            return false;
        }

        // Release the parking spot
        auto spot = ticket->getAssignedSpot();
        for (auto& floor : floors) {
            if (floor->getFloorNumber() == spot->getFloorNumber()) {
                floor->releaseSpot(spot);
                break;
            }
        }

        // Mark ticket as paid
        ticket->setStatus(TicketStatus::PAID);
        currentOccupancy--;

        // Remove from active tickets
        activeTickets.erase(ticketIt);

        std::cout << "✅ Payment completed! Spot released. Have a great day!\n";
        return true;
    }

    void displayAllBoards() const {
        std::cout << "\n╔════════════════════════════════════════╗\n";
        std::cout << "║   " << name << " - Status Board   ║\n";
        std::cout << "╚════════════════════════════════════════╝\n";
        std::cout << "Total Capacity: " << maxCapacity << "\n";
        std::cout << "Current Occupancy: " << currentOccupancy << "\n";
        std::cout << "Available Spots: " << (maxCapacity - currentOccupancy) << "\n";
        
        if (isFull()) {
            std::cout << "\n🚫 LOT FULL - NO ENTRY 🚫\n";
        }

        for (const auto& floor : floors) {
            floor->getDisplayBoard().display();
        }
    }

    int getCurrentOccupancy() const { return currentOccupancy; }
    int getMaxCapacity() const { return maxCapacity; }
};
