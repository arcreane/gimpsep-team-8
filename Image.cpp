#include <opencv2/opencv.hpp> 

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

        cv::namedWindow("Original Image", cv::WINDOW_NORMAL);
        cv::imshow("Original Image", imageMat);
        cv::waitKey(0);

        return 0; 
    }

 
    void saveImage(const std::string& newImagePath) {
        cv::imwrite(newImagePath, imageMat);
    }

 
    void displayImage() const {
        cv::imshow("Image", imageMat);
        cv::waitKey(0);
    }

    void applyTransformation() {

    }
};
