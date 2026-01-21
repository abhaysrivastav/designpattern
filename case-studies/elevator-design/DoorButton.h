#pragma once

#include "Button.h"
class DoorButton : public Button {
public:
    bool isPressed() const override { return pressed; }
};