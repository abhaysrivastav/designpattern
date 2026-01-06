#ifndef BUTTON_H
#define BUTTON_H

// Abstract Product 1: Button interface
class Button {
public:
    virtual ~Button() = default;
    virtual void render() const = 0;
    virtual void onClick() const = 0;
};

#endif // BUTTON_H