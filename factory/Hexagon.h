#ifndef HEXAGON_H
#define HEXAGON_H

#include "Shape.h"
#include <iostream>

// Concrete Product 4
class Hexagon : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a Hexagon" << std::endl;
    }

    std::string getType() const override {
        return "Hexagon";
    }
};

#endif // HEXAGON_H