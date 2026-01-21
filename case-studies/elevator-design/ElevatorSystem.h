#pragma once
#include <queue>
#include <vector>
#include "Building.h"
#include "Direction.h"
#include "ElevatorState.h"

struct FloorRequest {
    int floor;
    Direction dir;
    FloorRequest(int f, Direction d) : floor(f), dir(d) {}
};

class ElevatorSystem {
    static ElevatorSystem* system;
    Building* building;
    std::queue<FloorRequest> hallRequests;
    ElevatorSystem(int floors, int cars, int numPanels, int numDisplays)
        : building(new Building(floors, cars, numPanels, numDisplays)) {}
public:
    static ElevatorSystem* getInstance(int floors, int cars, int numPanels, int numDisplays) {
        if (!system)
            system = new ElevatorSystem(floors, cars, numPanels, numDisplays);
        return system;
    }
    ~ElevatorSystem() { delete building; }

    std::vector<ElevatorCar*>& getCars() { return building->getCars(); }
    Building* getBuilding() { return building; }

    void callElevator(int floorNum, Direction dir) {
        hallRequests.push(FloorRequest(floorNum, dir));
    }

    ElevatorCar* getNearestIdleCar(int floor) {
        ElevatorCar* best = nullptr;
        int minDist = INT32_MAX;
        for (auto car : building->getCars()) {
            if (car->getState() == ElevatorState::IDLE && !car->isInMaintenance() && !car->isOverloaded()) {
                int dist = abs(car->getCurrentFloor() - floor);
                if (dist < minDist) {
                    minDist = dist;
                    best = car;
                }
            }
        }
        return best;
    }

    void dispatcher() {
        while (!hallRequests.empty()) {
            FloorRequest req = hallRequests.front(); hallRequests.pop();
            ElevatorCar* car = getNearestIdleCar(req.floor);
            if (!car) {
                std::cout << "No idle car available; re-queueing request" << std::endl;
                hallRequests.push(req);
                break;
            }
            std::cout << "Dispatching Elevator " << (car->getId() + 1) << " to floor " << req.floor << std::endl;
            car->registerRequest(req.floor);
            car->move();
        }
    }

    void monitoring() {
        for (auto car : getCars())
            car->getDisplay().showElevatorDisplay(car->getId());
    }
};
ElevatorSystem* ElevatorSystem::system = nullptr;