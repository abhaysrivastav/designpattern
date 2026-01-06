#ifndef MAC_FACTORY_H
#define MAC_FACTORY_H

#include "UIFactory.h"
#include "MacButton.h"
#include "MacCheckbox.h"

// Concrete Factory: Creates Mac-family UI components
class MacFactory : public UIFactory {
public:
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<MacButton>();
    }

    std::unique_ptr<Checkbox> createCheckbox() const override {
        return std::make_unique<MacCheckbox>();
    }
};

#endif // MAC_FACTORY_H