# Parking Lot System - Low Level Design

## Overview
This is a comprehensive implementation of a parking lot management system demonstrating low-level object-oriented design principles for technical interviews, with actor-based architecture.

## Actors

### Primary Actor: Customer
**Responsibilities:**
- Parks their vehicle in the parking lot
- Obtains a parking ticket at entry
- Pays the parking fee at exit
- Exits the parking lot
- May request lost ticket assistance

### Secondary Actor: Admin
**Responsibilities:**
- Manages system resources (floors, spots)
- Configures pricing strategies
- Views reports and analytics
- Handles customer service issues
- Performs system maintenance
- Has role-based access control (SUPER_ADMIN, MANAGER, OPERATOR)

## Features Implemented

### Core Requirements (R1-R11)
- ✅ **R1**: Support for 40,000 vehicle capacity
- ✅ **R2**: Four parking spot types (Accessible, Compact, Large, Motorcycle)
- ✅ **R3**: Multiple entrance/exit points (architecture supports it)
- ✅ **R4**: Four vehicle types (Car, Truck, Van, Motorcycle)
- ✅ **R5**: Display boards showing real-time availability
- ✅ **R6**: Prevent entry when lot is full
- ✅ **R7**: Display "lot full" message
- ✅ **R8**: Parking ticket issuance at entry
- ✅ **R9**: Automated payment at exit
- ✅ **R10**: Configurable pricing (hourly rates, vehicle type, spot type)
- ✅ **R11**: Cash and card payment support

## Design Patterns Used

### 1. **Singleton Pattern**
- **Class**: `ParkingLot`
- **Purpose**: Ensure only one parking lot instance exists
- **Thread-safe**: Double-checked locking

### 2. **Factory Pattern**
- **Classes**: Vehicle hierarchy, ParkingSpot hierarchy
- **Purpose**: Flexible object creation

### 3. **Strategy Pattern**
- **Classes**: `PricingStrategy`, `HourlyPricingStrategy`, `LostTicketPricingStrategy`
- **Purpose**: Different pricing algorithms

### 4. **Inheritance & Polymorphism**
- **Vehicle**: Abstract base with Car, Truck, Van, Motorcycle
- **ParkingSpot**: Abstract base with CompactSpot, LargeSpot, etc.
- **Payment**: Abstract base with CashPayment, CardPayment
- **Person**: Abstract base with Admin, Customer

### 5. **Facade Pattern**
- **AdminPanel**: Simplifies complex admin operations
- Provides unified interface for system management

## Class Structure

### Core Classes
```
├── ParkingLot (Singleton)
│   AdminPanel (Facade)
│   └── Manages parking lot operations
├── Person (Abstract)
│   ├── Admin (role-based permissions)
│   └── Customer (parking users)
├── Vehicle (Abstract)
├── Payment (Abstract)
└── PricingStrategy (Abstract)
```

## Actor Roles and Permissions

### Admin Levels
| Level        | Add Floor | Update Pricing | View Reports | Manage Spots | Emergency Shutdown |
|--------------|-----------|----------------|--------------|--------------|-------------------|
| SUPER_ADMIN  | ✅        | ✅             | ✅           | ✅           | ✅                |
| MANAGER      | ✅        | ✅             | ✅           | ✅           | ❌                |
| OPERATOR     | ❌        | ❌             | ✅           | ✅           | ❌                | ├── ParkingTicket (Active tickets map)
│   └── PricingStrategy
├── Vehicle (Abstract)
├── Payment (Abstract)
└── PricingStrategy (Abstract)
```

## Vehicle to Spot Mapping

| Vehicle     | Can Park In                                      |
|-------------|--------------------------------------------------|
| Motorcycle  | Motorcycle, Compact, Large, Accessible (any)     |
| Car         | Compact, Large, Accessible                       |
| Van         | Large, Accessible                                |
| Truck       | Large only                                       |

## Pricing Logic

### Hourly Pricing Strategy
- **First hour**: $4.00
- **Additional hours**: $3.50/hour
- **Large spot premium**: +$1.00/hour
- **Motorcycle discount**: -25%
- **Truck surcharge**: +25%

### Lost Ticket
- **Flat rate**: $50.00 (maximum daily charge)

## Thread Safety

### Critical Sections Protected by Mutex
1. Ticket issuance
2. Spot assignment
3. Payment processing
4. Display board updates
5. Active ticket map access

## Building and Running

### Compilation
```bash
cd /workspaces/designpattern/case-studies/parking-lot
make
```

### Run Demo
```bash
makePerson.h                 # Person hierarchy (Admin/Customer)
├── AdminPanel.h             # Admin operations facade
├── main.cpp                 # Demo scenarios with actor
```

### Clean Build
```bash
make clean
```Actor Setup**: Creating admins (different levels) and customers
2. **Admin Login**: Super admin setting up the parking lot
3. **Floor Setup**: Admin adding floors with different configurations
4. **Customer Entry**: Multiple customers parking vehicles, ticket issuance
5. **Admin Monitoring**: Real-time occupancy reports
6. **Customer Exit**: Payment processing (cash and card)
7. **Lost Ticket**: Admin assists customer with lost ticket
8. **Access Control**: Testing role-based permissions
9. **Final Report**: Admin analytics and system status
├── ParkingFloor.h           # Floor management
├── ParkingSpot.h/cpp        # Spot types (Abstract + 4 concrete)
├── Vehicle.h                # Vehicle types (Abstract + 4 concrete)
├── ParkingTicket.h/cpp      # Ticket management
├── Payment.h/cpp            # Payment processing (Cash/Card)
├── PricingStrategy.h        # Pricing algorithms (Strategy pattern)
├── DisplayBoard.h           # Real-time availability display
├── main.cpp                 # Demo scenarios
├── Makefile                 # Build configuration
└── README.md                # This file
```

## Demo Scenarios

The `main.cpp` demonstrates:
1. **Setup**: Creating 3 floors with different spot configurations
2. **Entry**: Multiple vehicles entering, ticket issuance
3. **Display Updates**: Real-time board updates
4. **Exit & Payment**: Cash and card payments
5. **Lost Ticket**: Handling lost ticket scenario
6. **Capacity Management**: Display "lot full" when applicable

## Interview Discussion Points

### Scalability
- **Floor-based partitioning**: Easy to add more floors
- **Spot search optimization**: HashMap lookups, O(1) access
- **Distributed system**: Can extend to multiple parking lot locations

### Extensibility
- **New vehicle types**: Inherit from `Vehicle`, update spot mapping
- **New spot types**: Inherit from `ParkingSpot`
- **New payment methods**: Inherit from `Payment` (e.g., digital wallets)
- **New pricing strategies**: Implement `PricingStrategy` interface

### Concurrency
- **Mutex locks**: Protect critical sections
- **Deadlock prevention**: Single lock approach, short critical sections
- **Performance**: Lock-free reads where possible (const methods)

### SOLID Principles
- **Single Responsibility**: Each class has one clear purpose
- **Open/Closed**: Extensible via inheritance, closed for modification
- **Liskov Substitution**: All derived classes are substitutable
- **Interface Segregation**: Small, focused interfaces
- **Dependency Inversion**: Depend on abstractions (PricingStrategy, Payment)

## Common Interview Questions

### Q1: How do you handle high traffic at entry/exit?
**A**: Multiple entrance/exit panels, concurrent ticket processing with mutex locks, asynchronous payment processing

### Q2: How to optimize spot search?
**A**: Maintain availability counters per floor/type, early termination when floor is full, caching frequently used spots

### Q3: What if customer loses ticket?
**A**: Charge maximum daily r, users (customers/admins) to database
3. Restore state on system restart
4. Audit trail for payments and admin actions

### Q7: How to implement the actor model?
**A**:
1. Abstract `Person` base class
2. Derive `Admin` and `Customer` classes
3. Role-based access control for admins
4. AdminPanel as facade for admin operations
5. Customer actions through parking lot public API

### Q8: How to handle admin privileges?
**A**:
1. Define admin levels (SUPER_ADMIN, MANAGER, OPERATOR)
2. Check permissions before critical operations
3. Log all admin actions for audit trail
4. Implement authentication and session managementhicle type (e.g., Bus)?
**A**: 
1. Add `BUS` to `VehicleType` enum
2. Create `Bus` class inheriting from `Vehicle`
3. May need new spot type: `BusSpot`
4. Update spot mapping logic in `ParkingFloor::findAvailableSpot`

### Q5: How to implement reservations?
**A**: 
1. Add `ReservationSystem` class
2. Mark spots as "Reserved" (new state)
3. Time-based reservation expiry
4. Integration with ticket system

### Q6: Database integration?
**A**: 
1. Add persistence layer (Repository pattern)
2. Save tickets, transactions to database
3. Restore state on system restart
4. Audit trail for payments

## Time Complexity Analysis

| Operation              | Time Complexity | Notes                           |
|------------------------|-----------------|---------------------------------|
| Issue Ticket           | O(S)            | S = spots per floor (worst case)|
| Find Available Spot    | O(S)            | Linear search through spots     |
| Process Exit           | O(1)            | Hash map lookup                 |
| Complete Payment       | O(F)            | F = number of floors            |
| Display Board Update   | O(1)            | Direct counter update           |

## Space Complexity
- **Total**: O(S + V + T)
  - S = Total spots (40,000)
  - V = Active vehicles
  - T = Active tickets

## Future Enhancements
1. **Reservation System**: Pre-book spots
2. **VIP/Priority Parking**: Reserved areas
3. **Valet Service**: Separate workflow
4. **Time-based Discounts**: Weekend/evening rates
5. **Loyalty Program**: Frequent parker benefits
6. **Mobile App Integration**: QR code tickets
7. **Electric Vehicle Charging**: Special EV spots
8. **Analytics Dashboard**: Usage patterns, revenue reports
