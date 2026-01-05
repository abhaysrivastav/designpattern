#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
#include <iostream>

// Concrete Product 1
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a Circle" << std::endl;
    }
    
    std::string getType() const override {
        return "Circle";
    }
};

#endif // CIRCLE_H
