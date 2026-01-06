#ifndef WINDOWS_FACTORY_H
#define WINDOWS_FACTORY_H

#include "UIFactory.h"
#include "WindowsButton.h"
#include "WindowsCheckbox.h"

class WindowsFactory : public UIFactory
{

public:
    std::unique_ptr<Button> createButton() const override{
        return std::make_unique<WindowsButton>();
    }

    std::unique_ptr<Checkbox> createCheckbox() const override{
        return std::make_unique<WindowsCheckbox>();
    }
};

#endif
