#ifndef IMAGE_PROXY_H
#define IMAGE_PROXY_H

#include <string>
#include "Graphic.h"
#include "Image.h"

class ImageProxy : public Graphic {
private:
    std::string filename;
    Image* realImage;  // Pointer to the RealSubject (Image)

public:
    ImageProxy(const std::string& file);  // Constructor
    ~ImageProxy();                        // Destructor
    void draw() override;                 // Implementation of draw method
};

#endif // IMAGE_PROXY_H
