#include "WindowsFactory.h"
#include "MacFactory.h"
#include <iostream>

void renderUI(const UIFactory& factory) {
    std::cout << "\n--- Creating UI Components ---" << std::endl;
    
    // Create button using factory
    auto button = factory.createButton();
    // Create checkbox using factory
    auto checkbox = factory.createCheckbox();
    
    // Use them (render, click, toggle)
    button->render();
    button->onClick();
    
    checkbox->render();
    checkbox->toggle();
}

int main() {
    std::cout << "=== Abstract Factory Pattern Demo ===" << std::endl;
    
    std::cout << "\n=== Windows UI ===" << std::endl;
    WindowsFactory windowsFactory;
    renderUI(windowsFactory);
    
    std::cout << "\n=== Mac UI ===" << std::endl;
    MacFactory macFactory;
    renderUI(macFactory);
    
    std::cout << "\n=== THE MAGIC ✨ ===" << std::endl;
    std::cout << "Notice: renderUI() function works with BOTH factories!" << std::endl;
    std::cout << "It doesn't know about Windows or Mac - only UIFactory interface!" << std::endl;
    std::cout << "We can add Linux, Android factories without changing renderUI()!" << std::endl;
    
    return 0;
}