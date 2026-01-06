#ifndef MAC_BUTTON_H
#define MAC_BUTTON_H

#include "Button.h"
#include <iostream>

// Concrete Product: Mac-style Button
class MacButton : public Button {
public:
    void render() const override {
        std::cout << "Rendering the Mac Button " << std::endl;
    }

    void onClick() const override {
        std::cout << "Mac Button clicked" << std::endl;
    }
};

#endif // MAC_BUTTON_H