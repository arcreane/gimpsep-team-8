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
	/*Frontend app;
	app.run();
	return 0;
	*/

	Controller * controller = new Controller();
	Frontend frontend{ controller };

	frontend.load(argc, argv);

	return 0;
}