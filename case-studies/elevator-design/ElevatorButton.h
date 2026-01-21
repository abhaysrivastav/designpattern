#pragma once

#include "Button.h"
class ElevatorButton : public Button {
    int destinationFloor;
public:
    ElevatorButton(int floor) : destinationFloor(floor) {}
    int getDestinationFloor() const { return destinationFloor; }
    bool isPressed() const override { return pressed; }
};