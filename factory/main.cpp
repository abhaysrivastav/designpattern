#include "ShapeFactory.h"
#include <iostream>
#include <vector>
#include <memory>

int main() {
    std::cout << "=== Factory Design Pattern Demo ===" << std::endl;
    std::cout << std::endl;
    
    // Client code doesn't know about concrete classes (Circle, Rectangle, Triangle)
    // It only works with the Shape interface and ShapeFactory
    
    std::vector<std::string> shapeTypes = {"circle", "rectangle", "triangle", "hexagon"};
    
    for (const auto& type : shapeTypes) {
        std::cout << "Creating shape: " << type << std::endl;
        
        // Using factory to create objects
        std::unique_ptr<Shape> shape = ShapeFactory::createShape(type);
        
        if (shape) {
            std::cout << "  Type: " << shape->getType() << std::endl;
            std::cout << "  ";
            shape->draw();
        } else {
            std::cout << "  Error: Unknown shape type '" << type << "'" << std::endl;
        }
        std::cout << std::endl;
    }
    
    // Example: Adding new shapes without modifying client code
    std::cout << "=== Demonstrating Extensibility ===" << std::endl;
    auto myShape = ShapeFactory::createShape("Circle");
    if (myShape) {
        myShape->draw();
    }
    
    return 0;
}
