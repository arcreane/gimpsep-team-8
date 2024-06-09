#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <string>
#include <vector>

using namespace cv;
using namespace std;

// class which encapsulates all processing operations
class Image
{
public:
    Image() {}; // default constructor
    virtual ~Image() {} // Virtual destructor (proper cleanup in derived classes)
 
    void ResizeImage(const string& filepath, double scaleX, double scaleY);           // void ResizeImage(Mat image_source = imageSource, double scaleX, double scaleY);   
    void DilateImage(const string& filepath, int DilateSize, int DilateShape);
    void ErodeImage(const string& filepath, int erodeSize, int erodeType);
    void LightenDarkenImage(const string& filepath, double alpha, int beta);
    void EdgeDetectionImage(const string& filepath, double lowThreshold, double highThreshold, int kernelSize);
    void StitchingImage(int userchoice);
    
};

#endif
