#pragma once

#include "Button.h"
class EmergencyButton : public Button {
public:
    bool getPressed() const { return pressed; }
    void setPressed(bool val) { pressed = val; }
    bool isPressed() const override { return pressed; }
};