#ifndef SHAPE_H
#define SHAPE_H

#include <string>

// Abstract Product - Interface that all concrete products will implement
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    virtual std::string getType() const = 0;
};

#endif // SHAPE_H
