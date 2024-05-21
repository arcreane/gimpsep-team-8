#include "DilatationErosion.h"
#include <opencv2/imgproc/imgproc.hpp>

DilatationErosion::DilatationErosion(bool dilate, int size) : dilate(dilate), size(size) {}

void DilatationErosion::apply(Image& image) {
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * size + 1, 2 * size + 1));
    if (dilate) {
        cv::dilate(image.get_data(), image.get_data(), element);
    }
    else {
        cv::erode(image.get_data(), image.get_data(), element);
    }
}
