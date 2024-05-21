#include "Image.h"
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

//Surement à retirer
/*
Image::Image(const std::string& filepath) {
    load(filepath);
}*/

Mat Image::load(const string& filepath) {
    imageSource = imread(filepath, IMREAD_COLOR); //read the file
    if (imageSource.empty()) {
        cout << "Could not open or find the image";
    }
    Mat toto;
    resize(imageSource, toto, Size(), 800., 400., INTER_LINEAR);

    return imageSource;
}

Mat Image::save(const string& filepath) {
    imwrite(filepath, imageDestination);
    return imageDestination;
}

// potentiellement que cette fonction ne doit pas être appeler par le controlleur mais plutot à être utiliser comme dans le resize
void Image::display() { //faudra surement rajouter des trucs si l'utilisateur veut affichier differement ?
    // ! (window)
    namedWindow("Original Image", WINDOW_NORMAL); // Display windows and show for all images
    namedWindow("Modified Image", WINDOW_AUTOSIZE);
    // ! (imshow)
    imshow("Original Image", imageSource); // show our image inside it
   // imshow("Modified Image", imageDestination);
    // ! (wait)
    waitKey(0); // wait for a keystroke in the window
}

Mat Image::DilateImage(Mat image_source, double DilateSize)
{
    Mat dilateMat, dilateOutputImage, elementKernel;

    dilate(image_source, dilateOutputImage, elementKernel, Point(-1, -1), 1);
    return dilateOutputImage;
}

Mat Image::ErodeImage(Mat image_source, double erodeSize)
{
    Mat erodeMat, erodeOutputImage, elementKernel;

    //erode(image_source, erodeOutputImage, elementKernel, Point(-1, -1), 1) = getStructuringElement(MORPH_RECT, size(10, 10), );
    return erodeOutputImage;
}

void Image::ResizeImage( double scaleX, double scaleY) //potenntiellement en void car l'image de destination est dispo 
{
    resize(imageSource, imageDestination, Size(), scaleX, scaleY, INTER_LINEAR);
}



Mat& Image::get_data() { //qui a fait ça ?
    return imageDestination;
}
