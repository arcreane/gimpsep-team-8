#pragma once
#ifndef CANNYEDGEDETECTION_H
#define CANNYEDGEDETECTION_H

#include <opencv2/opencv.hpp>
#include "Transformation.h"

class CannyEdgeDetection : public Transformation {
private:
    double threshold1;
    double threshold2;
    int kernelSize;

public:
    CannyEdgeDetection(double t1, double t2, int kSize)
        : threshold1(t1), threshold2(t2), kernelSize(kSize) {}

    void apply(Image& image) const override {
        cv::Mat edges;
        cv::Canny(image.getImageMat(), edges, threshold1, threshold2, kernelSize);
        image.getImageMat() = edges;
    }
};

#endif // CANNYEDGEDETECTION_H
