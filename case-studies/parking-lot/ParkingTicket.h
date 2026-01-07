#pragma once
#include <string>
#include <memory>
#include <chrono>

class Vehicle;
class ParkingSpot;

enum class TicketStatus {
    ISSUED,
    IN_USE,
    PAID,
    VALIDATED,
    CANCELLED,
    LOST,
    REFUNDED
};

class ParkingTicket {
private:
    std::string ticketNumber;
    std::chrono::system_clock::time_point entryTime;
    std::chrono::system_clock::time_point exitTime;
    std::shared_ptr<Vehicle> vehicle;
    std::shared_ptr<ParkingSpot> assignedSpot;
    TicketStatus status;
    double amountDue;

    static int ticketCounter;

public:
    ParkingTicket(std::shared_ptr<Vehicle> v, std::shared_ptr<ParkingSpot> spot)
        : vehicle(v), assignedSpot(spot), status(TicketStatus::ISSUED), amountDue(0.0) {
        ticketNumber = "TKT-" + std::to_string(++ticketCounter);
        entryTime = std::chrono::system_clock::now();
    }

    std::string getTicketNumber() const { return ticketNumber; }
    
    std::chrono::system_clock::time_point getEntryTime() const { return entryTime; }
    
    void setExitTime(std::chrono::system_clock::time_point time) { exitTime = time; }
    
    std::chrono::system_clock::time_point getExitTime() const { return exitTime; }
    
    std::shared_ptr<Vehicle> getVehicle() const { return vehicle; }
    
    std::shared_ptr<ParkingSpot> getAssignedSpot() const { return assignedSpot; }
    
    TicketStatus getStatus() const { return status; }
    
    void setStatus(TicketStatus s) { status = s; }
    
    double getAmountDue() const { return amountDue; }
    
    void setAmountDue(double amount) { amountDue = amount; }

    // Calculate parking duration in hours
    double getParkingDurationInHours() const {
        auto duration = std::chrono::duration_cast<std::chrono::minutes>(
            exitTime - entryTime);
        return duration.count() / 60.0;
    }
};
