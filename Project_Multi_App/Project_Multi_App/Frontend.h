#ifndef FRONTEND_H
#define FRONTEND_H

#include <iostream>
#include <memory>
#include <deque>
#include <functional>

#include "CLI11.hpp"
#include "Controller.h"

using namespace cv;
using namespace std;

struct config_t
{
    // default values
    double width = 1.0;
    double height = 1.0;
    int shapesize = 2;
    int shapetype = 0;
    double contrast = 1.0;
    int brightness = 0;
    double lowThreshold = 2.0;
    double highThreshold = 5.0;
    int kernelSize = 8;
    int imagechoice = 0;
    string filechoosen = "../../images/human.jpg";
};

// class to manage the frontend interaction
class Frontend
{
public:
    Frontend() = default;
    Frontend(Controller controller);

    void load(int argc, char* argv[]); // function to load and parse command line arguments

private:
    void userAskForResize(double, double);
    void userAskForDilate(int dilatesize, int dilateshape); 
    void userAskForErode(int dilatesize, int dilateshape); 
    void userAskForLighting(double contrast, int brightness);
    void userAskForEdgeDetecting(double lowThreshold, double highThreshold, int kernelSize);
    void userAskForStitching(int userchoice);
    void additionalChecks(void) const; // additional checks to ensure valid configurations
    void loadedConfig(void); // load configuration settings
    void run(void); // main execution loop
     
    shared_ptr<CLI::App> _app; // pointer to the CLI11 app
    Controller _controller; // controller object to manage backend interactions

    string _config_name; // name of the configuration file
    struct config_t _config; // configuration settings

    deque<function<void()>> _pre_queue; // queue for pre-processing actions
    deque<function<void()>> _queue; // queue for processing actions
};

#endif