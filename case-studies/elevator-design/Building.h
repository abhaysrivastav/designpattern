#pragma once
#include <vector>
#include "Floor.h"
#include "ElevatorCar.h"

class Building {
    std::vector<Floor*> floors;
    std::vector<ElevatorCar*> cars;
public:
    Building(int numFloors, int numCars, int numPanels, int numDisplays) {
        int topFloor = numFloors - 1;
        for (int i = 0; i < numFloors; ++i)
            floors.push_back(new Floor(i, numPanels, numDisplays, topFloor));
        for (int i = 0; i < numCars; ++i)
            cars.push_back(new ElevatorCar(i, numFloors));
    }
    ~Building() {
        for (auto f : floors) delete f;
        for (auto c : cars) delete c;
    }
    std::vector<Floor*>& getFloors() { return floors; }
    std::vector<ElevatorCar*>& getCars() { return cars; }
};