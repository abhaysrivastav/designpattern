#include "ElevatorSystem.h"
#include "Direction.h"
#include <iostream>
#include <vector>
#include <random>
#include <ctime>

void runCall(ElevatorSystem* system, int floor, Direction dir)
{
    std::cout << "Passenger calls lift on floor " << floor << " (";
    if (dir == Direction::UP) std::cout << "UP";
    else if (dir == Direction::DOWN) std::cout << "DOWN";
    else std::cout << "IDLE";
    std::cout << ")" << std::endl;
    ElevatorCar* nearest = system->getNearestIdleCar(floor);
    if (!nearest) {
        std::cout << "No idle elevator available right now." << std::endl;
        return;
    }
    std::cout << "→ Nearest elevator is " << (nearest->getId() + 1)
        << " at floor " << nearest->getCurrentFloor()
        << ". Lift going ";
    if (dir == Direction::UP) std::cout << "UP";
    else if (dir == Direction::DOWN) std::cout << "DOWN";
    else std::cout << "IDLE";
    std::cout << "." << std::endl;

    system->callElevator(floor, dir);
    system->dispatcher();
    std::cout << "\n[Status after dispatch]" << std::endl;
    system->monitoring();
    std::cout << std::string(100, '-') << std::endl;
}

int main()
{
    int numFloors = 13;
    int numCars = 3;
    int numPanels = 1;
    int numDisplays = 3;

    ElevatorSystem* system = ElevatorSystem::getInstance(numFloors, numCars, numPanels, numDisplays);

    std::cout << "=== Scenario 1: Elevator 3 in maintenance, passenger calls elevator from floor 7 ===\n" << std::endl;
    system->monitoring();
    std::cout << std::endl;

    ElevatorCar* car3 = system->getCars()[2];
    car3->enterMaintenance();
    std::cout << std::endl;
    system->monitoring();
    std::cout << std::endl;

    runCall(system, 7, Direction::UP);

    car3->exitMaintenance();
    std::cout << "\n--- Resetting maintenance for all elevators ---\n" << std::endl;
    system->monitoring();
    std::cout << std::endl;

    std::cout << "=== Scenario 2: Random positions, passenger calls elevator from ground (0) to top (12) ===" << std::endl;
    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<int> dist(0, numFloors - 1);

    for (ElevatorCar* car : system->getCars()) {
        int randomFloor = dist(rng);
        std::cout << "\n== Setting random position for Elevator " << (car->getId() + 1) << " ==" << std::endl;
        std::cout << "→ Teleporting Elevator " << (car->getId() + 1) << " to floor " << randomFloor << std::endl;
        car->registerRequest(randomFloor);
        car->move();
    }

    std::cout << "\nElevator positions after random repositioning:" << std::endl;
    for (ElevatorCar* car : system->getCars()) {
        std::cout << "Elevator " << (car->getId() + 1)
            << " ► Floor: " << car->getCurrentFloor()
            << " | State: ";
        ElevatorState st = car->getState();
        if (st == ElevatorState::IDLE) std::cout << "IDLE";
        else if (st == ElevatorState::UP) std::cout << "UP";
        else if (st == ElevatorState::DOWN) std::cout << "DOWN";
        else if (st == ElevatorState::MAINTENANCE) std::cout << "MAINTENANCE";
        std::cout << std::endl;
    }
    std::cout << std::endl;

    runCall(system, 0, Direction::UP);

    return 0;
}