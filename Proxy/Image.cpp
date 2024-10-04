#include "Image.h"

// Constructor that accepts the filename and loads the image
Image::Image(const std::string& file) : filename(file) {
    loadImageFromDisk();
}

// Implementation of the draw method
void Image::draw() {
    std::cout << "Displaying image: " << filename << std::endl;
}

// Simulates loading the image from disk
void Image::loadImageFromDisk() {
    std::cout << "Loading image: " << filename << std::endl;
}
