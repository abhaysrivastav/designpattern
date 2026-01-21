#pragma once
#include <queue>
#include <iostream>
#include "Door.h"
#include "Display.h"
#include "ElevatorPanel.h"
#include "ElevatorState.h"
#include "Direction.h"

class ElevatorCar {
    int id;
    int currentFloor = 0;
    ElevatorState state = ElevatorState::IDLE;
    Door door;
    Display display;
    ElevatorPanel panel;
    std::queue<int> requestQueue;
    int load = 0;
    static const int MAX_LOAD = 680;
    bool overloaded = false;
    bool maintenance = false;
public:
    ElevatorCar(int id, int numFloors)
        : id(id), panel(numFloors)
    {
        updateDisplay();
    }
    int getId() const { return id; }
    int getCurrentFloor() const { return currentFloor; }
    ElevatorState getState() const { return state; }
    ElevatorPanel& getPanel() { return panel; }
    bool isInMaintenance() const { return maintenance; }
    bool isOverloaded() const { return overloaded; }

    void registerRequest(int floor) {
        if (maintenance) return;
        requestQueue.push(floor);
    }
    void move() {
        if (maintenance || overloaded || requestQueue.empty()) {
            state = ElevatorState::IDLE;
            updateDisplay();
            return;
        }
        int target = requestQueue.front(); requestQueue.pop();
        if (target == currentFloor) {
            stop();
            return;
        }
        state = (target > currentFloor) ? ElevatorState::UP : ElevatorState::DOWN;
        while (currentFloor != target && !maintenance && !overloaded) {
            currentFloor += (state == ElevatorState::UP ? 1 : -1);
            updateDisplay();
            display.showElevatorDisplay(id);
            std::cout << "Elevator " << (id + 1) << " passing floor " << currentFloor << std::endl;
        }
        stop();
    }
    void stop() {
        if (maintenance || overloaded) return;
        state = ElevatorState::IDLE;
        updateDisplay();
        door.open();
        std::cout << "Elevator " << (id + 1) << " doors opening at floor " << currentFloor << std::endl;
    }
    void enterMaintenance() {
        maintenance = true;
        state = ElevatorState::MAINTENANCE;
        door.close();
        updateDisplay();
        std::cout << ">>> Elevator " << (id + 1) << " entered MAINTENANCE mode" << std::endl;
    }
    void exitMaintenance() {
        maintenance = false;
        state = ElevatorState::IDLE;
        updateDisplay();
        std::cout << ">>> Elevator " << (id + 1) << " exited MAINTENANCE mode, now IDLE" << std::endl;
    }
    void emergencyStop() {
        state = ElevatorState::IDLE;
        overloaded = false;
        door.close();
        updateDisplay();
        std::cout << ">>> Elevator " << (id + 1) << " EMERGENCY STOP activated!" << std::endl;
    }
    void addLoad(int kg) {
        load += kg;
        if (load > MAX_LOAD) triggerOverloadAlarm();
        updateDisplay();
    }
    void removeLoad(int kg) {
        load -= kg;
        if (load <= MAX_LOAD) clearOverloadAlarm();
        updateDisplay();
    }
    Display& getDisplay() { return display; }
    Door& getDoor() { return door; }
private:
    void triggerOverloadAlarm() {
        overloaded = true;
        std::cout << "!!! Elevator " << (id + 1) << " OVERLOAD ALARM !!!" << std::endl;
    }
    void clearOverloadAlarm() {
        overloaded = false;
        std::cout << "Overload cleared for Elevator " << (id + 1) << "." << std::endl;
    }
    void updateDisplay() {
        Direction dir = state == ElevatorState::UP ? Direction::UP :
            state == ElevatorState::DOWN ? Direction::DOWN : Direction::IDLE;
        display.update(currentFloor, dir, load, state, overloaded, maintenance);
    }
};