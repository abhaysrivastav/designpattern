#include <iostream>
#include <thread>
#include <chrono>
#include "ParkingLot.h"
#include "Vehicle.h"
#include "Payment.h"

using namespace std;

// Helper function to simulate time passage
void simulateTimePassing(int seconds) {
    cout << "\n⏰ [Simulating " << seconds << " seconds passing...]\n";
    this_thread::sleep_for(chrono::seconds(seconds));
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗\n";
    cout << "║  Parking Lot Management System - Demo           ║\n";
    cout << "║  Low Level Object-Oriented Design               ║\n";
    cout << "╚══════════════════════════════════════════════════╝\n\n";

    // Get singleton instance
    ParkingLot* parkingLot = ParkingLot::getInstance("Downtown Parking Lot");

    // Create floors with different spot configurations
    cout << "🏗️  Setting up parking lot with 3 floors...\n\n";

    // Floor 1: Mixed spots
    auto floor1 = make_shared<ParkingFloor>(1);
    for (int i = 1; i <= 5; i++) {
        floor1->addSpot(make_shared<MotorcycleSpot>("F1-M" + to_string(i), 1));
    }
    for (int i = 1; i <= 10; i++) {
        floor1->addSpot(make_shared<CompactSpot>("F1-C" + to_string(i), 1));
    }
    for (int i = 1; i <= 8; i++) {
        floor1->addSpot(make_shared<LargeSpot>("F1-L" + to_string(i), 1));
    }
    for (int i = 1; i <= 3; i++) {
        floor1->addSpot(make_shared<AccessibleSpot>("F1-A" + to_string(i), 1));
    }
    parkingLot->addFloor(floor1);

    // Floor 2: More compact spots
    auto floor2 = make_shared<ParkingFloor>(2);
    for (int i = 1; i <= 15; i++) {
        floor2->addSpot(make_shared<CompactSpot>("F2-C" + to_string(i), 2));
    }
    for (int i = 1; i <= 5; i++) {
        floor2->addSpot(make_shared<LargeSpot>("F2-L" + to_string(i), 2));
    }
    for (int i = 1; i <= 2; i++) {
        floor2->addSpot(make_shared<AccessibleSpot>("F2-A" + to_string(i), 2));
    }
    parkingLot->addFloor(floor2);

    // Floor 3: Large vehicle focus
    auto floor3 = make_shared<ParkingFloor>(3);
    for (int i = 1; i <= 12; i++) {
        floor3->addSpot(make_shared<LargeSpot>("F3-L" + to_string(i), 3));
    }
    for (int i = 1; i <= 5; i++) {
        floor3->addSpot(make_shared<CompactSpot>("F3-C" + to_string(i), 3));
    }
    parkingLot->addFloor(floor3);

    // Display initial status
    parkingLot->displayAllBoards();

    cout << "\n\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    cout << "📋 SCENARIO 1: Multiple Vehicles Entering\n";
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";

    // Create vehicles
    auto car1 = make_shared<Car>("ABC-123");
    auto car2 = make_shared<Car>("XYZ-789");
    auto motorcycle1 = make_shared<Motorcycle>("BIKE-001");
    auto van1 = make_shared<Van>("VAN-555");
    auto truck1 = make_shared<Truck>("TRUCK-999");

    // Issue tickets
    auto ticket1 = parkingLot->issueTicket(car1);
    auto ticket2 = parkingLot->issueTicket(motorcycle1);
    auto ticket3 = parkingLot->issueTicket(van1);
    auto ticket4 = parkingLot->issueTicket(truck1);
    auto ticket5 = parkingLot->issueTicket(car2);

    parkingLot->displayAllBoards();

    // Simulate parking time
    simulateTimePassing(2);

    cout << "\n\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    cout << "📋 SCENARIO 2: Vehicle Exit and Payment\n";
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";

    // Car 1 exits - Cash payment
    if (ticket1) {
        cout << "🚗 Car ABC-123 is exiting...\n";
        double amount = parkingLot->processExit(ticket1->getTicketNumber());
        
        if (amount >= 0) {
            auto cashPayment = make_shared<CashPayment>(amount, 10.0);
            if (parkingLot->completePayment(ticket1->getTicketNumber(), cashPayment)) {
                cout << "💵 Cash received: $10.00 | Change: $" 
                     << cashPayment->getChange() << "\n";
            }
        }
    }

    cout << "\n";

    // Motorcycle exits - Card payment
    if (ticket2) {
        cout << "��️  Motorcycle BIKE-001 is exiting...\n";
        double amount = parkingLot->processExit(ticket2->getTicketNumber());
        
        if (amount >= 0) {
            auto cardPayment = make_shared<CardPayment>(
                amount, PaymentMethod::CREDIT_CARD, "4532123456789012", "John Doe");
            if (parkingLot->completePayment(ticket2->getTicketNumber(), cardPayment)) {
                cout << "💳 Card charged: " << cardPayment->getMaskedCardNumber() << "\n";
            }
        }
    }

    parkingLot->displayAllBoards();

    cout << "\n\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    cout << "📋 SCENARIO 3: More Vehicles Entering\n";
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";

    auto car3 = make_shared<Car>("CAR-333");
    auto motorcycle2 = make_shared<Motorcycle>("BIKE-002");
    
    parkingLot->issueTicket(car3);
    parkingLot->issueTicket(motorcycle2);

    parkingLot->displayAllBoards();

    simulateTimePassing(3);

    cout << "\n\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    cout << "📋 SCENARIO 4: Lost Ticket Case\n";
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";

    if (ticket3) {
        cout << "😰 Van VAN-555 lost the ticket!\n";
        ticket3->setStatus(TicketStatus::LOST);
        
        double amount = parkingLot->processExit(ticket3->getTicketNumber());
        cout << "⚠️  Lost ticket charge applied: $" << amount << "\n";
        
        auto payment = make_shared<CardPayment>(
            amount, PaymentMethod::DEBIT_CARD, "6011123456789012", "Jane Smith");
        parkingLot->completePayment(ticket3->getTicketNumber(), payment);
    }

    cout << "\n\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    cout << "📋 FINAL STATUS\n";
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";

    parkingLot->displayAllBoards();

    cout << "\n\n╔══════════════════════════════════════════════════╗\n";
    cout << "║              Demo Completed Successfully         ║\n";
    cout << "╚══════════════════════════════════════════════════╝\n";

    cout << "\n📚 Key Features Demonstrated:\n";
    cout << "   ✓ Singleton pattern (ParkingLot)\n";
    cout << "   ✓ Factory pattern (Vehicle/Spot creation)\n";
    cout << "   ✓ Strategy pattern (Pricing calculation)\n";
    cout << "   ✓ Multi-floor parking management\n";
    cout << "   ✓ Real-time display board updates\n";
    cout << "   ✓ Multiple payment methods (Cash/Card)\n";
    cout << "   ✓ Lost ticket handling\n";
    cout << "   ✓ Thread-safe operations (mutex locks)\n";
    cout << "   ✓ Vehicle-to-spot mapping logic\n\n";

    return 0;
}
