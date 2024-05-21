#ifndef CONTROLLER_H
#define CONTROLLER_H


class Image;
class Frontend;

class Controller
{
public:
	Controller();
	~Controller() = default;
	Controller(Image* _image_object, Frontend* _command_line);

	//void main();
	void askForResizing();
	void displayAllPhoto();
private:
	Image* _image;
	Frontend* _frontend;
};

#endif