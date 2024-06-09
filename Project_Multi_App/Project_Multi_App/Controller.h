#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>

using namespace std;

class Image;

class Controller
{
public:
	Controller() = default; // default constructor
	Controller(Controller&&) = default; // move constructor
	Controller& operator=(Controller&&) = default; // move assignment operator
	~Controller() {}; // destructor

	// sets the file path for image operations 
	inline void setFilepath(const string& filepath) { _filepath = filepath; }
	// retrieve the currently file path
	const string& filepath(void) const { return _filepath; }

	// delegate methods to Image class for performing image processing
	void askForResizing(double, double);
	void askForDilating(int, int);
	void askForEroding(int, int);
	void askForLighting(double, int);
	void askForEdgeDetecting(double, double, int);
	void askForStitching(int userchoice);

	string _filepath; // path to the image file used in operations
private:
	Image* _image; // pointer to an Image object that performs actual image operations
};

#endif