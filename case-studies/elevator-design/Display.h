#pragma once
#include "Direction.h"
#include "ElevatorState.h"
#include <iostream>
#include <string>

class Display {
    int floor = 0;
    int load = 0;
    Direction direction = Direction::IDLE;
    ElevatorState state = ElevatorState::IDLE;
    bool maintenance = false;
    bool overloaded = false;
public:
    void update(int f, Direction d, int l, ElevatorState s, bool ov, bool maint) {
        floor = f; direction = d; load = l; state = s; overloaded = ov; maintenance = maint;
    }
    void showElevatorDisplay(int carId) {
        std::string msg = maintenance ? "MAINTENANCE"
            : overloaded ? "OVERLOADED"
            : state == ElevatorState::IDLE ? "IDLE"
            : state == ElevatorState::UP ? "UP"
            : state == ElevatorState::DOWN ? "DOWN"
            : "UNKNOWN";
        std::cout << "Elevator " << (carId + 1)
            << " ► Floor: " << floor
            << " | Dir: " << (direction == Direction::UP ? "UP" : direction == Direction::DOWN ? "DOWN" : "IDLE")
            << " | Load: " << load
            << " | State: " << msg
            << std::endl;
    }
};