#ifndef FRONTEND_H
#define FRONTEND_H


#include "Controller.h"
#include <iostream>
#include <memory>
#include <deque>
#include <functional>
#include "CLI11.hpp"

struct config_t
{
    unsigned int width = 43;
    unsigned int height = 16;
    std::string filechoosen = "../../images/human.jpg";
};

class Frontend
{
public:
    Frontend() = default;
    explicit Frontend(Controller * controller);

    void load(int argc, char* argv[]);
    void run(void);

private:
    void additionalChecks(void) const;
    void loadedConfig(void);

    [[noreturn]] void exit(int exit_code) const;

    std::shared_ptr<CLI::App> _app;
    Controller* _controller;

    std::string _config_name;
    struct config_t _config;

    std::deque<std::function<void()>> _pre_queue;
    std::deque<std::function<void()>> _queue;
};

#endif