#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "Image.h"

class Transformation : public Image {
public:
    Mat TransformationDilate(Mat image_source, double DilateSize);
    Mat TransformationErode(Mat image_source, double erodeSize);
    Mat TransformationResize(Mat image_source, double scaleX, double scaleY);
    
    
    /*virtual void apply(Image& image) = 0;
    void resize_factors(double resize_scaleX, double resize_scaleY)
    {
        scaleX = resize_scaleX; scaleY = resize_scaleY;
    }
    virtual ~Transformation() {}*/
};

#endif
