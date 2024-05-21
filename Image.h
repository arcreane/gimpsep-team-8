#pragma once
#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <vector>

class Image {
private:
    std::vector<std::vector<int>> pixelIntensities; // Matrice d'intensités de pixels

public:
    // Constructeur par défaut
    Image();

    // Méthode pour charger une image
    void loadImage(const std::vector<std::vector<int>>& pixels);

    // Méthode pour sauvegarder une image
    void saveImage();

    // Méthode pour afficher l'image
    void displayImage() const;

    // Méthode pour appliquer une transformation sur l'image (à implémenter)
    void applyTransformation(/* Paramètres de la transformation */);
};

#endif // IMAGE_H
