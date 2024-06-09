#include <opencv2/imgproc/imgproc.hpp> // Normalement à supprimer

#include "Frontend.h"

using namespace cv;
using namespace std;

// constructor initializing the controller with a move operation to take ownership of the passed controller object
Frontend::Frontend(Controller controller)
{
    _controller = move(controller);
}

// loads the application configuration and sets up command line argument parsing
void Frontend::load(int argc, char* argv[])
{
    _app = make_shared<CLI::App>("Project Multi App"); // initializes the CLI app

    // config file setup
    _app->set_config("--config", _config_name, "Read a config file", false);
    auto image = _app->add_option_group("Image", "Possible filepath image");
    image->add_option("--filepath", _controller._filepath, "Set image choosen path")->type_name("FILE");
    
    int calib_num = 1;

    // define input command options
    auto input = _app->add_option_group("input", "Possible inputs");
    input
        ->add_option_function<vector<double>>(
            "--size",
            [&](const vector<double>& v)
            {
                _config.width = v.at(0);
                _config.height = v.at(1);
            },
            "Set size to resize an image")
        ->type_name("    WIDTH HEIGHT")
        ->type_size(2);
    input
        ->add_option_function<vector<int>>(
            "--shape_type",
            [&](const vector<int>& v)
            {
                _config.shapetype = v.at(0);
            }, 
            "Choose between 0-MORPH_RECT 1-MORPH_CROSS 2-MORPH_ELLIPSE")
        ->type_name("SHAPE TYPE")
        ->type_size(1);
    input
        ->add_option_function<vector<int>>(
            "--shape_size",
            [&](const vector<int>& v)
            {
                _config.shapesize = v.at(0);
            },
            "Set shape size to dilate or erode an image")
        ->type_name("SHAPE SIZE")
        ->type_size(1);
    input
        ->add_option_function<vector<double>>(
            "--contrast",
            [&](const vector<double>& v)
            {
                _config.contrast = v.at(0);
            },
            "Set contrast value between [1.0-3.0]")
        ->type_name("    CONTRAST")
        ->type_size(1);
    input
        ->add_option_function<vector<int>>(
            "--brightness",
            [&](const vector<int>& v)
            {
                _config.brightness = v.at(0);
            },
            "Set brightness value between [-100 - 100]")
        ->type_name("BRIGHTNESS")
        ->type_size(1);
    input
        ->add_option_function<vector<double>>(
            "--lowthold",
            [&](const vector<double>& v)
            {
                _config.lowThreshold = v.at(0);
            },
            "Set low threshold value")
        ->type_name("   LOW THOLD")
        ->type_size(1);
    input
        ->add_option_function<vector<double>>(
            "--highthold",
            [&](const vector<double>& v)
            {
                _config.highThreshold = v.at(0);
            },
            "Set high threshold value")
        ->type_name(" HIGH THOLD")
        ->type_size(1);
    input
        ->add_option_function<vector<int>>(
            "--kernel_size",
            [&](const vector<int>& v)
            {
                _config.kernelSize = v.at(0);
            },
            "Set kernel size value")
        ->type_name("KRNL SIZE")
        ->type_size(1);
    input
        ->add_option_function<vector<int>>(
            "--img_choice",
            [&](const vector<int>& v)
            {
                _config.imagechoice = v.at(0);
            },
            "Choose image to stitch between 0-CONTORSIONIST 1-SPIDERMAN")
        ->type_name("IMG CHOICE")
        ->type_size(1);

    // define action command options
    auto action = _app->add_option_group("action", "Possible actions");
    auto resize = action->add_subcommand("resize", "Resize an image")
        ->callback([&]() { this->userAskForResize(_config.width, _config.height); });
    auto dilate = action->add_subcommand("dilate", "Dilate an image")
        ->callback([&]() { this->userAskForDilate(_config.shapesize, _config.shapetype); });
    auto erode = action->add_subcommand("erode", "Erode an image")
        ->callback([&]() { this->userAskForErode(_config.shapesize, _config.shapetype); });
    auto lightendarken = action->add_subcommand("lighting", "Change image intensity")
        ->callback([&]() { this->userAskForLighting(_config.contrast, _config.brightness); });
    auto edgedetecting = action->add_subcommand("detecting", "Edges image detecting")
        ->callback([&]() { this->userAskForEdgeDetecting(_config.lowThreshold, _config.highThreshold, _config.kernelSize); });
    auto stitch = action->add_subcommand("stitching", "Stitch an image")
        ->callback([&]() { this->userAskForStitching(_config.imagechoice); });

    // Attempt to parse the command line arguments provided by the user
    try
    {
        _app->parse(argc, argv);
        this->additionalChecks();
    }
    catch (const CLI::ParseError& e)
    {
        _app->exit(e);
    }

    this->loadedConfig();

    this->run();

    cout << "Program exited with code 0" << endl;
}

// resizes an image according to user-specified dimensions
void Frontend::userAskForResize(double width, double height)
{
    cout << "Width : " << width << " Height : " << height << endl; //log
    // queues the resize operation to be executed
    _queue.emplace_back([&, width, height]() mutable {
        cout << "Resize your image ..." << endl;
        _controller.askForResizing(width, height);
        });
}

// applies dilation to an image with specified size and shape
void Frontend::userAskForDilate(int dilatesize, int dilatetype)
{
    cout << "Size : " << dilatesize << " Type : " << dilatetype << endl; //log
    // queues the dilation operation to be executed
    _queue.emplace_back([&, dilatesize, dilatetype]() mutable {
        cout << "Dilate your image ..." << endl;
        _controller.askForDilating(dilatesize, dilatetype);
        });
}


// applies erosion to an image with specified size and type
void Frontend::userAskForErode(int erodesize, int erodetype)
{
    cout << "Size : " << erodesize << " Type : " << erodetype << endl; //log
    // queues the erosion operation to be executed
    _queue.emplace_back([&, erodesize, erodetype]() mutable {
        cout << "Erode your image ..." << endl;
        _controller.askForEroding(erodesize, erodetype);
        });
}

// modifies the lighting of an image using specified contrast and brightness values
void Frontend::userAskForLighting(double contrast, int brightness)
{
    cout << "Contrast : " << contrast << " Brightness : " << brightness << endl; //log
    // queues the lighting operation to be executed
    _queue.emplace_back([&, contrast, brightness]() mutable {
        cout << "Lighting your image ..." << endl;
        _controller.askForLighting(contrast, brightness);
        });
}

// detects edges in an image using specified thresholds and kernel size
void Frontend::userAskForEdgeDetecting(double lowThreshold, double highThreshold, int kernelSize)
{
    cout << "Low Threshold : " << lowThreshold << " High Threshold : " << highThreshold << " Kernel Size : " << kernelSize << endl; //log
    // queues the edge detecting operation to be executed
    _queue.emplace_back([&, lowThreshold, highThreshold, kernelSize]() mutable {
        cout << "Edge Detecting of your image ..." << endl;
        _controller.askForEdgeDetecting(lowThreshold, highThreshold, kernelSize);
        });
}

// stitches multiple images together based on user choice
void Frontend::userAskForStitching(int userchoice)
{
    // queues the stitching operation to be executed
    _queue.emplace_back([&, userchoice]() mutable {
        cout << "Stitching of your images ..." << endl;
        _controller.askForStitching(userchoice);
        });
}

// checks if necessary conditions are met before performing an action
void Frontend::additionalChecks() const
{
    // throws an error if required conditions are not met
    if ((_app->get_option_group("action")->got_subcommand("resize")
        && _controller._filepath.empty()))
    {
        throw CLI::RequiresError("resize", "resize");
    }
    else if ((_app->get_option_group("action")->got_subcommand("dilate")
        && _controller._filepath.empty()))
    {
        throw CLI::RequiresError("dilate", "dilate");
    }
}

// loads the configuration from a specified file
void Frontend::loadedConfig()
{
    _config_name = (_app->get_option("--config")->results().empty()) ?
        _config_name :
        _app->get_option("--config")->results().at(0);
    ifstream test{ _config_name };
    _config_name = (!test.good()) ? "None" : _config_name;
    cout << "Config file loaded: " << (_config_name.empty() ? "None" : _config_name)
        << endl;
}

// runs the queued operations
void Frontend::run()
{
    while (!_pre_queue.empty())
    {
        _pre_queue.front()();
        _pre_queue.pop_front();
    }

    while (!_queue.empty())
    {
        _queue.front()();
        _queue.pop_front();
    }
}
