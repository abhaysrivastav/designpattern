#pragma once

#include "Button.h"
#include "Direction.h"
class HallButton : public Button {
    Direction direction;
public:
    HallButton(Direction dir) : direction(dir) {}
    Direction getDirection() const { return direction; }
    bool isPressed() const override { return pressed; }
};