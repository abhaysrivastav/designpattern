#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <iostream>
#include "Graphic.h"

class Image : public Graphic {
private:
    std::string filename;

public:
    Image(const std::string& file);  // Constructor
    void draw() override;            // Implementation of draw method
    void loadImageFromDisk();        // Loads image from disk
};

#endif // IMAGE_H
