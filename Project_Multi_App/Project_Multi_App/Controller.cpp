#include "Controller.h"
#include "Image.h"
#include "Frontend.h"

using namespace cv;
using namespace std;


// delegate the resize request to the Image class
void Controller::askForResizing(double width, double height) {
	cout << "IN askForResizing into Controller.cpp " << endl; // log entry
	_image->ResizeImage(_filepath, width, height); // call the ResizeImage function of Image class
	cout << "OUT askForResizing into Controller.cpp " << endl; // log exit
}

// delegate the dilation request to the Image class
void Controller::askForDilating(int dilatesize, int dilatetype) {
	cout << "IN askForDilating into Controller.cpp " << endl; // log entry
	_image->DilateImage(_filepath, dilatesize, dilatetype); // call the DilateImage function of Image class
	cout << "OUT askForDilating into Controller.cpp " << endl; // log exit
}

// delegate the eroding request to the Image class
void Controller::askForEroding(int erodesize, int erodetype) {
	cout << "IN askForEroding into Controller.cpp " << endl; // log entry
	_image->ErodeImage(_filepath, erodesize, erodetype); // call the ErodeImage function of Image class
	cout << "OUT askForEroding into Controller.cpp " << endl; // log exit
}

// delegate the lighting adjustment request to the Image class
void Controller::askForLighting(double contrast, int brightness) {
	cout << "IN askForLighting into Controller.cpp " << endl; // log entry
	_image->LightenDarkenImage(_filepath, contrast, brightness); // call the LightenDarkenImage function of Image class
	cout << "OUT askForLighting into Controller.cpp " << endl; // log exit
}

// delegate the edge detecting request to the Image class
void Controller::askForEdgeDetecting(double lowThreshold, double highThreshold, int kernelSize) {
	cout << "IN askForEdgeDetecting into Controller.cpp " << endl; // log entry
	_image->EdgeDetectionImage(_filepath, lowThreshold, highThreshold, kernelSize); // call the EdgeDetectionImage function of Image class
	cout << "OUT askForEdgeDetecting into Controller.cpp " << endl; // log exit
}

// delegate the image stitching request to the Image class
void Controller::askForStitching(int userchoice) { 
	cout << "IN askForStitching into Controller.cpp " << endl; // log entry
	_image->StitchingImage(userchoice); // call the StitchingImage function of Image class
	cout << "OUT askForStitching into Controller.cpp " << endl; // log exit
}