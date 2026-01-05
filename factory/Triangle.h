#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"
#include <iostream>

// Concrete Product 3
class Triangle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a Triangle" << std::endl;
    }
    
    std::string getType() const override {
        return "Triangle";
    }
};

#endif // TRIANGLE_H
