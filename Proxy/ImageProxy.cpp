#include "ImageProxy.h"

// Constructor to initialize the proxy with the filename
ImageProxy::ImageProxy(const std::string& file) : filename(file), realImage(nullptr) {}

// Destructor to clean up the realImage if it was created
ImageProxy::~ImageProxy() {
    delete realImage;
}

// The draw method, which lazily loads the real image if necessary
void ImageProxy::draw() {
    if (realImage == nullptr) {
        realImage = new Image(filename);  // Load the real image only when needed
    }
    realImage->draw();  // Delegate the draw call to the real image
}
