#include <opencv2/imgproc/imgproc.hpp> // Normalement à supprimer
#include "Controller.h"
#include "Image.h"
#include "Frontend.h"

using namespace cv;
using namespace std;

Controller::Controller() 
	:_image {new Image()}
{
}
#if 0
// Le main doit prendre en compte le choix de l'utilisateur dans la ligne de commande et de ce fait appeler la bonne fonction
// dans la classe Image  
void Controller::main() {
	askForResizing(); // à retirer potentiellement 

	_frontend->run(); //exemple de comment appeler les fonctions avec les bons pointeurs
	//selon le choix de l'utilisateur il faut declencher la bonne fonction de Image

	//_image->load(""); //exemple de comment appeler les fonctions avec les bons pointeurs

}
// Faut il un switch case pour prendre en compte le choix de l'utilisateur ?
#endif

// à retirer potentiellement
void Controller::askForResizing() {
	Mat imageLoaded;
	//Mat* image_destination;
	_image->load("C:/Users/Charles Radolanirina/VSWS/images/human.jpg");
	//image_destination = 
	_image->ResizeImage(800, 545.5);
	//_image->save("C:/Users/Charles Radolanirina/VSWS/images/image_modifiee.jpg");
	displayAllPhoto();
}

void Controller::displayAllPhoto() {
	_image->display();
}