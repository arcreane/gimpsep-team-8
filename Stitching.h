#ifndef STITCHING_H
#define STITCHING_H

#include <opencv2/opencv.hpp>
#include <opencv2/stitching.hpp>
#include "Transformation.h"
#include <vector>
#include <string>

class Stitching : public Transformation {
private:
    std::vector<std::string> imagePaths;

public:
    Stitching(const std::vector<std::string>& imagePaths) : imagePaths(imagePaths) {}

    void apply(Image& image) const override {
        std::vector<cv::Mat> images;
        for (const std::string& path : imagePaths) {
            cv::Mat img = cv::imread(path);
            if (img.empty()) {
                std::cerr << "Erreur : Impossible de charger l'image " << path << std::endl;
                return;
            }
            images.push_back(img);
        }

        cv::Mat pano;
        cv::Stitcher::Mode mode = cv::Stitcher::PANORAMA;
        cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(mode);
        cv::Stitcher::Status status = stitcher->stitch(images, pano);

        if (status != cv::Stitcher::OK) {
            std::cerr << "Erreur de stitching, code d'erreur = " << int(status) << std::endl;
            return;
        }

        image.getImageMat() = pano;
    }
};

#endif // STITCHING_H
