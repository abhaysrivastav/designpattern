#pragma once
#include "DoorState.h"
class Door {
    DoorState state = DoorState::CLOSED;
public:
    void open() { state = DoorState::OPEN; }
    void close() { state = DoorState::CLOSED; }
    bool isOpen() const { return state == DoorState::OPEN; }
    DoorState getState() const { return state; }
};