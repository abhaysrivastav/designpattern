#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"
#include <iostream>

// Concrete Product 2
class Rectangle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a Rectangle" << std::endl;
    }
    
    std::string getType() const override {
        return "Rectangle";
    }
};

#endif // RECTANGLE_H
