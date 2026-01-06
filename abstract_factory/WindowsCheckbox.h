#ifndef WINDOWS_CHECKBOX_H
#define WINDOWS_CHECKBOX_H

#include "Checkbox.h"
#include <iostream>

// Concrete Product: Windows-style Checkbox
class WindowsCheckbox : public Checkbox {
public:
    void render() const override {
        std::cout << "Rendering the Windows Checkbox " << std::endl;
    }

    void toggle() const override {
        std::cout << " Windows button toggled .... " << std::endl;
    }
};

#endif // WINDOWS_CHECKBOX_H