#include <iostream>
#include "proxy_image.h"
#include <vector>
#include <memory>

int main() {
    std::vector<std::unique_ptr<Image>> images;

    images.push_back(std::make_unique<ProxyImage>("photo1.jpg"));
    images.push_back(std::make_unique<ProxyImage>("photo2.png"));
    images.push_back(std::make_unique<ProxyImage>("photo3.bmp"));

    std::cout << "\n--- Accessing image properties without loading ---\n";
    for (const auto& img : images) {
        img->getProperties();
    }

    std::cout << "\n--- Displaying images (this will trigger loading) ---\n";
    for (const auto& img : images) {
        img->display();
    }

    std::cout << "\n--- Accessing image properties after loading ---\n";
    for (const auto& img : images) {
        img->getProperties();
    }

    return 0;
}