#pragma once

class Button {
protected:
    bool pressed = false;
public:
    virtual ~Button() = default;
    virtual void pressDown() { pressed = true; }
    virtual void reset() { pressed = false; }
    virtual bool isPressed() const = 0;
};