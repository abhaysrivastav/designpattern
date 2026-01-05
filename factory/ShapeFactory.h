#ifndef SHAPE_FACTORY_H
#define SHAPE_FACTORY_H

#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Hexagon.h"
#include <memory>
#include <string>
#include <algorithm>

// Factory Class - Encapsulates object creation logic
class ShapeFactory {
public:
    // Factory Method - Creates objects based on input
    static std::unique_ptr<Shape> createShape(const std::string& shapeType) {
        // Convert to lowercase for case-insensitive comparison
        std::string type = shapeType;
        std::transform(type.begin(), type.end(), type.begin(), ::tolower);
        
        if (type == "circle") {
            return std::make_unique<Circle>();
        } else if (type == "rectangle") {
            return std::make_unique<Rectangle>();
        } else if (type == "triangle") {
            return std::make_unique<Triangle>();
        } else if (type == "hexagon") {
            return std::make_unique<Hexagon>();
        }
        
        // Return nullptr for unknown types
        return nullptr;
    }
};

#endif // SHAPE_FACTORY_H
