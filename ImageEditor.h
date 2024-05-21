#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include "Image.h"
#include "DilatationErosion.h"
#include "Resizing.h"
#include "Stitching.h"

class ImageEditor {
private:
    Image image;

public:
    void loadImage(const char* imagePath) {
        if (image.loadImage(imagePath) != 0) {
            std::cerr << "Erreur lors du chargement de l'image." << std::endl;
        }
    }

    void saveImage(const std::string& newImagePath) {
        image.saveImage(newImagePath);
    }

    void displayImage() {
        image.displayImage();
    }

    void applyTransformation(const Transformation& transformation) {
        transformation.apply(image);
    }
    void applyStitching(const std::vector<std::string>& imagePaths) {
       Stitching stitching(imagePaths);
        stitching.apply(image);
    }
};

#endif // IMAGEEDITOR_H
