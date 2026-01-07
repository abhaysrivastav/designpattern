#include "ParkingLot.h"

// Initialize static members
ParkingLot* ParkingLot::instance = nullptr;
std::mutex ParkingLot::instanceMutex;
