#ifndef RESIZING_H
#define RESIZING_H

#include <opencv2/opencv.hpp>
#include "Transformation.h"

class Resizing : public Transformation {
private:
    double scaleFactor;   // Facteur de redimensionnement
    int newWidth;         // Nouvelle largeur (optionnel)
    int newHeight;        // Nouvelle hauteur (optionnel)
    bool useScaleFactor;  // Indicateur pour utiliser le facteur de redimensionnement ou les dimensions

public:
    // Constructeur pour redimensionnement par facteur
    Resizing(double scaleFactor) : scaleFactor(scaleFactor), newWidth(0), newHeight(0), useScaleFactor(true) {}

    // Constructeur pour redimensionnement par dimensions
    Resizing(int width, int height) : scaleFactor(0), newWidth(width), newHeight(height), useScaleFactor(false) {}

    void apply(Image& image) const override {
        cv::Mat resizedImage;
        if (useScaleFactor) {
            cv::resize(image.getImageMat(), resizedImage, cv::Size(), scaleFactor, scaleFactor);
        }
        else {
            cv::resize(image.getImageMat(), resizedImage, cv::Size(newWidth, newHeight));
        }
        image.getImageMat() = resizedImage;
    }
};

#endif // RESIZING_H
