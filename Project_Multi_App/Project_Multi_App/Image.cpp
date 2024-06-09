#include "Image.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/stitching.hpp>

using namespace cv;
using namespace std;

// function which applies dilation to an image, enhancing features.
void Image::DilateImage(const string& filepath, int DilateSize, int DilateType)
{
    cout << "Dilate ongoing " <<endl; // log entry
    
    // matrices declaration
    Mat sourceDilate, dilation_dst, elementKernel; 
    sourceDilate = imread(filepath); // load the image from the specified filepath

    // check if the user enter bad inputs 
    if (sourceDilate.empty())
    {
        cout << "Could not open or find the image" << endl;
        return;
    }
    else if (DilateType < 0 || DilateType > 2) // choose 0, 1 or 2
    {
        cout << "Could not process erode action due to bad shape type choosen" << endl;
        return;
    }
    else if (DilateSize < 0) // no negative number
    {
        cout << "Could not process erode action due to negative size choosen" << endl;
        return;
    }

    // create the structuring element using the specified size and shape
    elementKernel = getStructuringElement(DilateType, Size(2 * DilateSize + 1, 2 * DilateSize + 1), Point(DilateSize, DilateSize));
        
    dilate(sourceDilate, dilation_dst, elementKernel); // perform the dilation operation
    imwrite("../../../images/dilated.jpg", dilation_dst); // save the dilated image to a file

    // ! (window)
    namedWindow("Original Image", WINDOW_AUTOSIZE); // Display windows and show for all images
    namedWindow("Dilated Image", WINDOW_AUTOSIZE);
    // ! (imshow)
    imshow("Original Image", sourceDilate); // show our image inside it
    imshow("Dilated Image", dilation_dst);
    // ! (wait)

    waitKey(0); // wait for a keystroke in the window
    cout << "Dilate DONE " << endl; // log exit
}

// function which applies erosion to an image, reducing noise
void Image::ErodeImage(const string& filepath, int erodeSize, int erodeType)
{
    cout << "Erode ongoing " <<endl; // log entry

    // matrices declaration
    Mat sourceErode, erode_dst, elementKernel;
    sourceErode = imread(filepath); // load the image from the specified filepath

    // check if the user enter bad inputs 
    if (sourceErode.empty())
    { 
        cout << "Could not open or find the image" << endl;
        return;
    }
    else if (erodeType < 0 || erodeType > 2) // choose 0, 1 or 2
    {
        cout << "Could not process erode action due to bad shape type choosen" << endl;
        return;
    }
    else if (erodeSize < 0) // no negative number
    {
        cout << "Could not process erode action due to negative size choosen" << endl;
        return;
    }
    
    // create the structuring element using the specified size and shape
    elementKernel = getStructuringElement(erodeType, Size(2 * erodeSize + 1, 2 * erodeSize + 1), Point(erodeSize, erodeSize));

    erode(sourceErode, erode_dst, elementKernel); // perform the erosion operation
    imwrite("../../../images/eroded.jpg", erode_dst); // save the eroded image to a file

    // ! (window)
    namedWindow("Original Image", WINDOW_AUTOSIZE); // Display windows and show for all images
    namedWindow("Eroded Image", WINDOW_AUTOSIZE);
    // ! (imshow)
    imshow("Original Image", sourceErode); // show our image inside it
    imshow("Eroded Image", erode_dst);
    // ! (wait)

    waitKey(0); // wait for a keystroke in the window
    cout << "Erode DONE " << endl; // log exit
}

// function which resizes an image by scaling factors along the x and y axes
void Image::ResizeImage(const string& filepath, double scaleX, double scaleY) 
{
    cout << "Resize ongoing " << scaleX << " " << scaleY << endl; // log entry
    
    // matrices declaration
    Mat Source, Destination;
    Source = imread(filepath); // load the image from the specified filepath
    
    // check if the user enter bad inputs 
    if (Source.empty()) {
        cout << "Could not open or find the image" << endl;
        return;
    }
    else if (scaleX < 0 || scaleY < 0) // no negative number
    {
        cout << "Could not process resize action due to negative size choosen" << endl;
        return;
    }

    resize(Source, Destination, Size(), scaleX, scaleY, INTER_LINEAR); // perform the resize operation
    imwrite("../../../images/resized.jpg", Destination); // save the resized image to a file

    // ! (window)
    namedWindow("Original Image", WINDOW_NORMAL); // Display windows and show for all images
    namedWindow("Resized Image", WINDOW_AUTOSIZE);
    // ! (imshow)
    imshow("Original Image", Source); // show our image inside it
    imshow("Resized Image", Destination);
    // ! (wait)
    waitKey(0); // wait for a keystroke in the window
    cout << "Resize DONE " << endl; // log exit
}

// function which modifies the brightness and contrast of an image
void Image::LightenDarkenImage(const string& filepath, double contrast, int brightness)
{
    cout << "Lighten&Darken ongoing " << contrast << " " << brightness << endl; // log entry
    
    // matrices declaration
    Mat Source;
    Source = imread(filepath); // load the image from the specified filepath
    
    // check if the user enter bad inputs 
    if (Source.empty()) {
        cout << "Could not open or find the image" << endl;
        return;
    }
    else if (contrast < 1.0 || contrast > 3.0) // choose between 1.0 and 3.0
    {
        cout << "Could not process lighting action due to wrong contrast value" << endl;
        return;
    }
    else if (brightness < -100 || brightness > 100) // choose between -100 and 100
    {
        cout << "Could not process lighting action due to wrong brightness value" << endl;
        return;
    }

    // initialize a new image matrix with the same size and type as the source
    Mat new_image = Mat::zeros(Source.size(), Source.type());

    // iterate over each pixel to adjust brightness and contrast
    for (int y = 0; y < Source.rows; y++) {
        for (int x = 0; x < Source.cols; x++) {
            for (int c = 0; c < Source.channels(); c++) {
                new_image.at<Vec3b>(y, x)[c] =
                    saturate_cast<uchar>(contrast * Source.at<Vec3b>(y, x)[c] + brightness); // apply the new brightness and contrast
            }
        }
    }

    // ! (window)
    namedWindow("Original Image", WINDOW_NORMAL); // Display windows and show for all images
    namedWindow("Modified Image", WINDOW_AUTOSIZE);
    // ! (imshow)
    imshow("Original Image", Source); // show our image inside it
    imshow("Modified Image", new_image);
    // ! (wait)
    waitKey(0); // wait for a keystroke in the window
    cout << "Lighten&Darken DONE " << endl; // log exit
}

// function which detects edges in an image using the Canny algorithm
void Image::EdgeDetectionImage(const string& filepath, double lowThreshold, double highThreshold, int kernelSize)
{
    cout << "Edge Detection ongoing " << endl; // log entry
    
    // matrices declaration
    Mat sourceEdgeDetection, edgedetection_dst, elementKernel;
    sourceEdgeDetection = imread(filepath); // load the image from the specified filepath
    
    // check if the user enter bad inputs 
    if (sourceEdgeDetection.empty())
    {
        cout << "Could not open or find the image" << endl;
        return;
    }
    else if (lowThreshold < 0 || highThreshold < 0 || lowThreshold >= highThreshold) // no negative number + low threshold need to be under high threshold
    {
        cout << "Invalid threshold values. Ensure lowThreshold < highThreshold and both are non-negative" << endl;
        return;
    }
    else if (kernelSize <= 0 || kernelSize % 2 == 0) // need to be a odd number
    {
        cout << "Could not process detecting action due to negative size choosen or size is not odd" << endl;
        return;
    }

    // applying Gaussian Blur to smooth the image, using kernelSize
    GaussianBlur(sourceEdgeDetection, sourceEdgeDetection, Size(kernelSize, kernelSize), 0);
        
    Canny(sourceEdgeDetection, edgedetection_dst, lowThreshold, highThreshold); // performing Canny edge detection
    imwrite("../../../images/edgedetected.jpg", edgedetection_dst); // save the edge detected image to a file

    // ! (window)
    namedWindow("Original Image", WINDOW_AUTOSIZE); // Display windows and show for all images
    namedWindow("Modified Image", WINDOW_AUTOSIZE);
    // ! (imshow)
    imshow("Original Image", sourceEdgeDetection); // show our image inside it
    imshow("Modified Image", edgedetection_dst);
    // ! (wait)
    waitKey(0); // wait for a keystroke in the window
    
    cout << "Edge Detection DONE " << endl; // log exit
}

// function which creates a panorama or a stitched image from multiple images
void Image::StitchingImage(int userchoice)
{
    cout << "Stitching ongoing " << endl; // log entry
    
    // matrices declaration
    Mat imageSource, StitchedImage;
    vector<Mat> images;
    vector<string> imagePaths;

    if (userchoice == 0) // choose 0 for contortionist
    {
        imagePaths = { "../../../images/contorsionist_left.jpg", "../../../images/contorsionist_center.jpg", "../../../images/contorsionist_right.jpg"};
    }
    else if (userchoice == 1) // choose 0 for spiderman
    {
        imagePaths = { "../../../images/spiderman_left.jpg", "../../../images/spiderman_center.jpg", "../../../images/spiderman_right.jpg" };
    }
    else // enter a bad input
    {
        cout << "Error : please enter 0 or 1" << endl;
        return;
    }
    
    // load images from the specified file paths (imagePaths)
    for (const auto& path : imagePaths) {
        imageSource = imread(path);
        if (!imageSource.empty()) {
            images.push_back(imageSource);
        }
    }

    // ensure there are enough images to create a panorama
    if (images.size() < 3) {
        cout << "Need more images to create a panorama." << endl;
        return;
    }
    
    // instance creation of Stitcher in PANORAMA mode
    Stitcher::Mode mode = Stitcher::PANORAMA;
    Ptr<Stitcher> stitcher = Stitcher::create(mode);
    Stitcher::Status status = stitcher->stitch(images, StitchedImage);
       
    // check the stitch works
    if (status != Stitcher::OK) {
        cout << "Stitching could not be completed successfully. Error code: " << int(status) << endl;
    }
    else {
        cout << "Stitching completed successfully." << endl;

        // display each of the original images
        for (const auto& show : images) {
            // ! (window)
            namedWindow("Original Image", WINDOW_AUTOSIZE); // Display windows and show for all images
            // ! (imshow)
            imshow("Original Image", show); // show our image inside it
            waitKey(0);
        }
        // ! (window)
        namedWindow("Stitched Image", WINDOW_AUTOSIZE); 
        // ! (imshow)
        imshow("Stitched Image", StitchedImage);
    }
    // ! (wait)
    waitKey(0); // wait for a keystroke in the window
    cout << "Stitching DONE " << endl; // log exit
}
