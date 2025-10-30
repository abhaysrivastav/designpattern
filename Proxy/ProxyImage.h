#ifndef PROXY_IMAGE_H
#define PROXY_IMAGE_H

#include "image.h"
#include "real_image.h"
#include <memory>
#include <iostream>

class ProxyImage : public Image {
private:
    std::string filename;
    std::unique_ptr<RealImage> realImage;

    void loadRealImage() {
        if (!realImage) {
            realImage = std::make_unique<RealImage>(filename);
        }
    }

public:
    explicit ProxyImage(const std::string& file) : filename(file), realImage(nullptr) {
        std::cout << "ProxyImage created for: " << filename << " (not loaded yet)" << std::endl;
    }

    void display() override {
        loadRealImage();  // Lazy loading happens here!
        realImage->display();
    }

    void getProperties() override {
        if (realImage) {
            realImage->getProperties();
        } else {
            std::cout << "Image: " << filename << " [Not loaded yet]" << std::endl;
        }
    }
};

#endif // PROXY_IMAGE_H