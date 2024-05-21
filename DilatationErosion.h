#ifndef DILATATIONEROSION_H
#define DILATATIONEROSION_H

#include <opencv2/opencv.hpp>
#include "Transformation.h"

enum Operation {
    ERODE,
    DILATE
};

class DilatationErosion : public Transformation {
private:
    int size;
    Operation operation;

public:
    DilatationErosion(int size, Operation operation) : size(size), operation(operation) {}

    void apply(Image& image) const override {
        cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * size + 1, 2 * size + 1), cv::Point(size, size));
        if (operation == ERODE) {
            cv::erode(image.getImageMat(), image.getImageMat(), element);
        }
        else {
            cv::dilate(image.getImageMat(), image.getImageMat(), element);
        }
    }
};

#endif // DILATATIONEROSION_H
