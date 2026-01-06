#ifndef WINDOWS_BUTTON_H
#define WINDOWS_BUTTON_H

#include "Button.h"
#include <iostream>

// Concrete Product: Windows-style Button
class WindowsButton : public Button {
public:
    void render() const override {
        std::cout << "Rendering the Windows Button " << std::endl;
    }

    void onClick() const override {
        std::cout << "Windows Button clicked" << std::endl;
    }
};

#endif // WINDOWS_BUTTON_H