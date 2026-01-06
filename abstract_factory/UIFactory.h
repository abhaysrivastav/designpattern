#ifndef UI_FACTORY_H
#define UI_FACTORY_H

#include "Button.h"
#include "Checkbox.h"
#include <memory>
#include <iostream>

class UIFactory {
public:
    // Your methods here
    virtual ~UIFactory() = default;
    virtual std::unique_ptr<Button> createButton() const = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() const = 0;

};

#endif