#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/opencv.hpp>
#include <iostream>

class Image {
private:
    cv::Mat imageMat;

public:
    int loadImage(const char* imagePath) {
        imageMat = cv::imread(imagePath);
        if (imageMat.empty()) {
            std::cerr << "Erreur : Impossible de charger l'image." << std::endl;
            return -1;
        }
        return 0;
    }

    void saveImage(const std::string& newImagePath) {
        cv::imwrite(newImagePath, imageMat);
    }

    void displayImage(const std::string& windowName = "Image") const {
        cv::imshow(windowName, imageMat);
        cv::waitKey(0);
    }
    
    cv::Mat& getImageMat() {
        return imageMat;
    }

    const cv::Mat& getImageMat() const {
        return imageMat;
    }
};

#endif // IMAGE_H
