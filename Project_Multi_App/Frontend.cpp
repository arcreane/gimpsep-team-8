#include <opencv2/imgproc/imgproc.hpp> // Normalement à supprimer

#include "Frontend.h"
#include "Controller.h"

using namespace cv;
using namespace std;

Frontend::Frontend(Controller * controller)
    :_controller{ controller }

{}

void Frontend::load(int argc, char* argv[])
{
    _app = make_shared<CLI::App>("Project Multi App");
    _config_name = "./config.ini";

    // config file
    _app->set_config("--config", _config_name, "Read a config file", false);
    auto image = _app->add_option_group("Image");
    image->add_option("--filepath", _config.filechoosen, "Set image choosen path")->type_name("FILE");

    auto action = _app->add_option_group("action", "Possible actions");
    auto resize = action->add_option_function<vector<unsigned int>>(
        "--resize",
        [this](const vector<unsigned int>& v) {
            _config.width = v.at(0);
            _config.height = v.at(1);
        },
        "Set Image size expected in mm")
        ->type_name("WIDTH HEIGHT")
        ->type_size(2);


    /*auto print = action->add_subcommand("print", "Print label")
                     ->callback([this, &print_num]() { this->addPrint(print_num); })
                     ->immediate_callback();
    print->add_option("print_num", print_num, "Number of copies")->type_name("N");
    */
    action->require_subcommand();

    try
    {
        _app->parse(argc, argv);
        this->additionalChecks();
    }
    catch (const CLI::ParseError& e)
    {
        _app->exit(e);
        //exit(-1);
    }

    this->loadedConfig();

    this->run();

    cout << "Program exited with code 0" << endl;
}

void Frontend::additionalChecks() const
{
    if ((_app->get_option_group("action")->got_subcommand("resize")
        && _config.filechoosen.empty()))
    {
        throw CLI::RequiresError("resize", "resize");
    }
}

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


    if (_controller) {
        _controller->askForResizing();
    }
}

#if 0
[[noreturn]] void Frontend::exit(int exit_code) const
{
    cout << "Program exited with code " << exit_code << endl;
    exit(exit_code);
}
#endif