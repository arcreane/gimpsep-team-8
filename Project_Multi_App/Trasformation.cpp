#include "Transformation.h"
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std; 


//DilatationErosion::DilatationErosion(int)
//void DilatationErosion::

Mat Transformation::TransformationDilate(Mat image_source, double DilateSize) {
    Mat dilateMat, dilateOutputImage, elementKernel;

    dilate(image_source, dilateOutputImage, elementKernel, Point(-1,-1),1);
    return dilateOutputImage;
}

Mat Transformation::TransformationErode(Mat image_source, double erodeSize) {
    Mat erodeMat, erodeOutputImage, elementKernel;

//    erode(image_source, erodeOutputImage, elementKernel, Point(-1, -1), 1) = getStructuringElement(MORPH_RECT, size(10, 10), );
    return erodeOutputImage;
}

//Transformation::Transformation(bool dilate, int size) : dilate(dilate), size(size) {}

Mat Transformation::TransformationResize(Mat image_source, double scaleX, double scaleY) {
    Mat image_destination;
    
    resize(image_source, image_destination, Size(), scaleX, scaleY, INTER_LINEAR);
    return image_destination;
}
