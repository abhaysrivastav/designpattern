# Parking Lot System - Low Level Object-Oriented Design

## Actors

### Primary Actor
**Customer**: 
- Parks their vehicle in the parking lot
- Obtains a parking ticket at entry
- Pays the parking fee at exit
- Exits the parking lot
- May lose ticket and request lost ticket handling

### Secondary Actor
**Admin**: 
- Manages system resources (parking spots, floors)
- Configures entry/exit panels
- Sets and updates pricing strategies
- Manages system configuration
- Views reports and analytics
- Handles customer issues and disputes
- Maintains parking lot capacity settings

## Requirements Analysis

### Functional Requirements
- **R1**: Support 40,000 vehicle capacity
- **R2**: Support 4 parking spot types (Accessible, Compact, Large, Motorcycle)
- **R3**: Multiple entrance/exit points
- **R4**: Support 4 vehicle types (Car, Truck, Van, Motorcycle)
- **R5**: Display boards showing availa
- **Admin** - System administrator with management privileges
- **Customer** - End user who parks vehiclesble spots
- **R6**: Prevent entry when lot is full
- **R7**: Display "lot full" message
- **R8**: Issue parking tickets at entry
- **R9**: Automated payment at exit
- **R10**: Configurable pricing based on vehicle/spot type and duration
- **R11**: Accept card and cash payments

## Actors

### Primary Actor
- **Customer**: Parks their vehicle, obtains a parking ticket, pays the parking fee, and exits the parking lot

### Secondary Actor
- **Admin**: Manages system resources (parking spots, entry/exit panels, pricing), handles account and system configuration

## Design Approach - Bottom-Up Strategy

Following a **bottom-up approach**, we design fundamental entities first, then combine them into complex components:

1. **Smallest entities**: Vehicle, ParkingSpot, Payment (abstract classes)
2. **Support entities**: Person, Address, Account
3. **Core components**: ParkingTicket, DisplayBoard, Entrance/Exit
4. **Main system**: ParkingLot (coordinates all components)

### 1. Key Entities Identification

#### Core Entities (Abstract Classes)
- **Vehicle** - Abstract base (Car, Truck, Van, Motorcycle) - *Inheritance*
- **ParkingSpot** - Abstract base (Compact, Large, Accessible, Motorcycle) - *Inheritance*
- **Account** - Abstract base (Admin, Customer) - *Inheritance*
- **Payment** - Abstract base (Cash, CreditCard) - *Inheritance*

#### Concrete Components
- **ParkingLot** - Main system coordinator, singleton - *Composition*
- **ParkingFloor** - Floor management
- **Entrance** - Issues tickets at entry - *Association*
- **Exit** - Validates tickets at exit - *Association*
- **ParkingTicket** - Tracks parking session - *Association*
- **DisplayBoard** - Shows availability - *Association*
- **PricingStrategy** - Calculates parking fees

#### Supporting Classes
- **Person** - Stores person information
- **Address** - Custom data type for location

Person (Abstract)
├── Admin (system management)
└── Customer (parking user)
│   ├── ParkingSpot[]
│   │   ├── CompactSpot
│   │   ├── LargeSpot
│   │   ├── MotorcycleSpot
│   │   └── AccessibleSpot
│   └── DisplayBoard
├── EntrancePanel[]
├── ExitPanel[]
└── PricingStrategy

Vehicle (Abstract)
├── Car
├── Truck
├── Van
└── Motorcycle

Payment (Abstract)
├── CashPayment
└── CardPayment

ParkingTicket
└── References Vehicle, ParkingSpot
```

## Detailed Class Design

### Enumerations and Custom Data Types

#### Why Abstract Classes over Enums for Vehicles/Spots?
**Enumeration Approach**: Creates user-defined data type with fixed values
- ❌ **Violates Open/Closed Principle** - Modifying enums requires changes in multiple places
- ❌ **Not Scalable** - Adding new vehicle types means updating all switch statements
- ❌ **No Behavior** - Enums can't have methods or properties

**Abstract Class Approach**: 
- ✅ **Follows Open/Closed Principle** - Extend by adding new classes, don't modify existing code
- ✅ **Scalable** - New vehicle types just inherit from base class
- ✅ **Rich Behavior** - Classes can have methods, properties, and polymorphism

**Note**: We still use enums for status types (PaymentStatus, AccountStatus, TicketStatus) as these are fixed and won't require frequent modifications.

```cpp
// Enums for status tracking (fixed values, unlikely to change)
enum class PaymentStatus {
    PENDING,
    COMPLETED,
    FAILED,
    CANCELLED,
    REFUNDED
};

enum class AccountStatus {
    ACTIVE,
    BLOCKED,
    CANCELLED,
    CLOSED
};

enum class TicketStatus {
   Class Relationships

### 1. Association (Loose Coupling)
**Definition**: Loose relationship where one class refers to another to use its functionality. Associated objects can exist independently.

**Examples in Our System**:
- `ParkingSpot` ↔ `Vehicle` (0..1 to 1): Spot tracks which vehicle occupies it
- `Vehicle` ↔ `ParkingTicket` (1 to 1): Vehicle has one ticket when parked
- `ParkingTicket` → `Entrance`, `Exit`, `Vehicle`: Ticket references entry/exit points
- `DisplayBoard` → `ParkingSpot` (1 to 0..*): Board displays status of multiple spots

### 2. Composition (Strong Ownership)
**Definition**: Strong whole-part relationship. When parent is destroyed, components are destroyed. Components don't exist independently.

**Examples in Our System**:
- `ParkingLot` ◆→ `Entrance` (1 to 1..*): Lot owns all entrances
- `ParkingLot` ◆→ `Exit` (1 to 1..*): Lot owns all exits
- `ParkingLot` ◆→ `ParkingSpot` (1 to 1..*): Lot owns all spots
- `ParkingLot` ◆→ `ParkingTicket` (1 to 0..*): Lot manages active tickets
- `ParkingLot` ◆→ `DisplayBoard` (1 to 0..*): Lot owns display boards
- `ParkingLot` ◆→ `ParkingRate` (1 to 1): Lot has one rate policy
- `ParkingTicket` ◆→ `Payment` (1 to 1): Ticket owns its payment transaction

### 3. Inheritance (IS-A Relationship)
**Definition**: Child class inherits behavior and attributes from parent. Enables code reuse and polymorphism.

**Examples in Our System**:
- `Vehicle` ◁── `Car`, `Truck`, `Van`, `Motorcycle`
- `ParkingSpot` ◁── `CompactSpot`, `LargeSpot`, `AccessibleSpot`, `MotorcycleSpot`
- `Payment` ◁── `Cash`, `CreditCard`
- `Account` ◁── `Admin`, `Customer`

### Multiplicity Table

| Source | Target | Multiplicity | Reason |
|--------|--------|--------------|--------|
| ParkingLot | Entrance | 1 -- 1..* | Must have ≥1 entrance for traffic flow |
| ParkingLot | Exit | 1 -- 1..* | Must have ≥1 exit for smooth operation |
| ParkingLot | ParkingSpot | 1 -- 1..* | Lot manages multiple spots |
| ParkingLot | ParkingTicket | 1 -- 0..* | Zero or more active tickets |
| ParkingLot | DisplayBoard | 1 -- 0..* | Boards per floor/entrance |
| ParkingLot | ParkingRate | 1 -- 1 | One rate policy per lot |
| ParkingSpot | Vehicle | 0..1 -- 1 | Spot can be empty or have 1 vehicle |
| Vehicle | ParkingTicket | 1 -- 1 | Vehicle has 1 ticket when parked |
| ParkingTicket | Payment | 1 -- 1 | Each ticket has 1 payment |
| DisplayBoard | ParkingSpot | 1 -- 0..* | Board shows status of spots |

### Design Patterns Used

1. **Singleton Pattern**: ParkingLot (only one instance)
2. **Factory Pattern**: Vehicle creation, Spot creation
3. **Strategy Pattern**: Pricing calculation, Payment processing
4. **Composition Pattern**: ParkingLot owns and manages all component
    REFUNDED
};

// Vehicle and Spot types use ABSTRACT CLASSES (see below)
// This follows SOLID principles and allows extensibility
```
5. **Command Pattern**: Admin actions (add floor, update pricing, etc.)
6. **Facade Pattern**: Admin interface simplifies complex system operations

### Design Patterns Used

1. **Singleton Pattern**: ParkingLot (only one instance)
2. **Factory Pattern**: Vehicle creation, Spot creation
3. **Strategy Pattern**: Pricing calculation, Payment processing
4. **Observer Pattern**: DisplayBoard updates when spot availability changes

## Key Design Decisions

### 1. Vehicle-to-Spot Mapping
- **Motorcycle** → MotorcycleSpot, CompactSpot, LargeSpot, AccessibleSpot (any)
- **Car** → CompactSpot, LargeSpot, AccessibleSpot
- **Van** → LargeSpot, AccessibleSpot
- **Truck** → LargeSpot

### 2. Thread Safety
- Use mutex/locks for:
  - Spot assignment
  - Ticket generation
  - Payment processing
  - Display board updates

### 3. Scalability Considerations
- Floor-based partitioning (40,000 spots across multiple floors)
- Efficient spot search using availability maps
- Cache frequently accessed data

### 4. Pricing Strategy
- Hourly rates vary by vehicle type
- First hour: $4
- Additional hours: $3.50/hour
- Premium for large spots: +$1/hour

## Implementation Notes

See `/case-studies/parking-lot/` directory for complete C++ implementation with:
- Header files for each class
- Implementation files
- Main demonstration program
- Makefile for compilation

## Interview Tips

### Common Questions
1. **How do you handle concurrency?** 
   - Use mutex locks for critical sections (spot assignment, payment)
   
2. **How to optimize spot search?**
   - Maintain availability count per floor
   - Use hash maps for O(1) spot lookup
   
3. **What if a customer loses their ticket?**
   - Charge maximum daily rate
   - Create "lost ticket" handling in payment logic

4. **How to handle different payment methods?**
   - Strategy pattern for payment processing
   - Abstract Payment class with Card/Cash implementations

5. **Extensibility for new vehicle/spot types?**
   - Use factory pattern
   - Open/Closed principle - extend without modifying existing code
