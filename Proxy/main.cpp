#include "ImageProxy.h"
#include "Image.h"

int main() {
    // The client creates an ImageProxy object instead of directly creating an Image object.
    Graphic* image1 = new ImageProxy("image1.png");
    Graphic* image2 = new ImageProxy("image2.png");

    // The image is not loaded yet; it will only be loaded when we call draw().
    image1->draw();  // Loads and displays "image1.png"
    image2->draw();  // Loads and displays "image2.png"

    // Clean up
    delete image1;
    delete image2;

    return 0;
}
