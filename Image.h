#pragma once
#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <vector>

class Image {
private:
    std::vector<std::vector<int>> pixelIntensities; // Matrice d'intensit�s de pixels

public:
    // Constructeur par d�faut
    Image();

    // M�thode pour charger une image
    void loadImage(const std::vector<std::vector<int>>& pixels);

    // M�thode pour sauvegarder une image
    void saveImage();

    // M�thode pour afficher l'image
    void displayImage() const;

    // M�thode pour appliquer une transformation sur l'image (� impl�menter)
    void applyTransformation(/* Param�tres de la transformation */);
};

#endif // IMAGE_H
