#ifndef MAC_CHECKBOX_H
#define MAC_CHECKBOX_H

#include "Checkbox.h"
#include <iostream>

// Concrete Product: Mac-style Checkbox
class MacCheckbox : public Checkbox {
public:
    void render() const override {
        std::cout << "Rendering the Mac Checkbox " << std::endl;
    }

    void toggle() const override {
        std::cout << " Mac button toggled .... " << std::endl;
    }
};

#endif // MAC_CHECKBOX_H