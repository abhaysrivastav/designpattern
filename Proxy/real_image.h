#ifndef REAL_IMAGE_H
#define REAL_IMAGE_H

#include "image.h"
#include <iostream>
#include <thread>
#include <chrono>

class RealImage : public Image {
private:
    std::string filename;
    int width;
    int height;

    void loadFromDisk() {
        std::cout << "Loading image from disk: " << filename << std::endl;
        // Simulate expensive loading operation
        std::this_thread::sleep_for(std::chrono::seconds(2));
        width = 1920;
        height = 1080;
        std::cout << "Image loaded successfully!" << std::endl;
    }

public:
    explicit RealImage(const std::string& file) : filename(file), width(0), height(0) {
        loadFromDisk();
    }

    void display() override {
        std::cout << "Displaying image: " << filename << std::endl;
    }

    void getProperties() override {
        std::cout << "Image: " << filename 
                  << " [" << width << "x" << height << "]" << std::endl;
    }
};

#endif // REAL_IMAGE_H