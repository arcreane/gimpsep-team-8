#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include "Image.h"
#include "Transformation.h"
#include <string>

class ImageEditor {
public:
    void load_image(const std::string& filepath);
    void save_image(const std::string& filepath);
    void apply_transformation(Transformation* transformation);
    void display_image();

private:
    Image currentImage;
};

#endif
