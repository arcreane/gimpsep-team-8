#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;
using namespace std;

class Image
{
private:
    Mat imageDestination, imageSource;  //ImageSource est l'image que l'on va charger, et ImageData celle que l'on va creer après modif

public:
    Image() {};
    virtual ~Image() {}
    Mat load(const string& filepath);
    Mat save(const string& filepath);
    void display(); // pas encore verifier l'utilisation potentiellement à mettre en private pour bloquer l'utilisation par le controller 

    Mat DilateImage(Mat image_source, double DilateSize); //pas encore verifier
    Mat ErodeImage(Mat image_source, double erodeSize); // pas encore verifier

    void ResizeImage(double scaleX, double scaleY);           // void ResizeImage(Mat image_source = imageSource, double scaleX, double scaleY);   



    Mat& get_data(); // pour quoi faire ?

    //Transformation* _transform; // à voir si on met pas tout dans une seule classe pour faciliter le tout
};

#endif
