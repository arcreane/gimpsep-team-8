#include <opencv2/opencv.hpp> 
#include <iostream>
#include <string>
#include "Frontend.h"
#include "Controller.h"
#include "CLI11.hpp"

using namespace cv;

using namespace std;

int main(int argc, char** argv)
{
	// create a Controller instance
	Controller controller{};
	// create a Frontend instance and move the controller into it
	Frontend frontend{ std::move(controller) };

	// load the frontend with command-line arguments
	// this function will parse command-line arguments and execute the appropriate actions
	frontend.load(argc, argv);

	return 0;
}