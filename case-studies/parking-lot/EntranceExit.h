#pragma once
#include <string>
#include <memory>
#include "ParkingTicket.h"
#include "Vehicle.h"

// Entrance class - issues parking tickets
class Entrance {
private:
    std::string entranceId;
    std::string location;

public:
    Entrance(const std::string& id, const std::string& loc)
        : entranceId(id), location(loc) {}

    std::string getEntranceId() const { return entranceId; }
    std::string getLocation() const { return location; }

    // This method would integrate with ParkingLot to issue tickets
    // The actual ticket issuance is handled by ParkingLot::issueTicket()
    void displayWelcomeMessage() const {
        std::cout << "🚪 Entrance " << entranceId << " - Welcome to the Parking Lot!\n";
    }
};

// Exit class - validates tickets before allowing exit
class Exit {
private:
    std::string exitId;
    std::string location;

public:
    Exit(const std::string& id, const std::string& loc)
        : exitId(id), location(loc) {}

    std::string getExitId() const { return exitId; }
    std::string getLocation() const { return location; }

    // Validates ticket payment status
    bool validateTicket(std::shared_ptr<ParkingTicket> ticket) const {
        if (!ticket) {
            std::cout << "❌ Invalid ticket!\n";
            return false;
        }

        TicketStatus status = ticket->getStatus();
        
        if (status == TicketStatus::PAID || status == TicketStatus::VALIDATED) {
            std::cout << "✅ Ticket validated. Gate opening...\n";
            ticket->setStatus(TicketStatus::VALIDATED);
            return true;
        }

        std::cout << "❌ Ticket not paid! Please pay at the payment kiosk.\n";
        return false;
    }

    void displayExitMessage() const {
        std::cout << "🚪 Exit " << exitId << " - Thank you for parking with us!\n";
    }
};
