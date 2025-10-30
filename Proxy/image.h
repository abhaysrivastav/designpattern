#ifndef IMAGE_H
#define IMAGE_H

#include <string>

// Subject Interface
class Image {
public:
    virtual ~Image() = default;
    virtual void display() = 0;
    virtual void getProperties() = 0;
};

#endif // IMAGE_H