
#include <opencv2/opencv.hpp>
#include <iostream>
#include "ImageEditor.h"
#include "DilatationErosion.h"
#include "Resizing.h"
#include <vector>

int main() {
    ImageEditor editor;
    //editor.loadImage("res/man.jpg");  // Remplacez par le chemin de votre image
    /*
    DilatationErosion dilateTransform(3, DILATE);
    editor.applyTransformation(dilateTransform);
    editor.displayImage(); // Afficher l'image après dilatation
   
    DilatationErosion erodeTransform(3, ERODE);
    editor.applyTransformation(erodeTransform);
    editor.displayImage(); // Afficher l'image après érosion
   
  

    // Appliquer le redimensionnement par facteur
    Resizing resizeTransformByFactor(0.5); // Réduire la taille de l'image par un facteur de 0.5
    editor.applyTransformation(resizeTransformByFactor);
    editor.displayImage(); // Afficher l'image redimensionnée

    // Appliquer le redimensionnement par dimensions
    Resizing resizeTransformByDimensions(800, 600); // Redimensionner l'image à 800x600
    editor.applyTransformation(resizeTransformByDimensions);
    editor.displayImage(); // Afficher l'image redimensionnée
      */

    std::vector<std::string> imagePaths = { "res/avion.png", "res/avion2.png"};
    editor.applyStitching(imagePaths);
    editor.displayImage();

    editor.saveImage("res/test.jpg");  // Remplacez par le chemin où vous voulez sauvegarder l'image

    return 0;
}
