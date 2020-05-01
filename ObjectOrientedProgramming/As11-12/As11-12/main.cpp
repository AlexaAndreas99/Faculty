#include "As1112.h"
#include <QtWidgets/QApplication>
#include "Controller.h"
#include "Gui.h"
#include "FileRepo.h"
#include "CSVRepo.h"
#include "HTMLRepo.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	Controller* ctrl = nullptr;
	FileRepo* r = new CSVRepo("data.txt");
	FileRepo* wa = new HTMLRepo("file.html");
	ctrl = new Controller(r, wa);
	Gui h{ctrl};
	h.show();
	//Dog d{ "asd","qwe","www",2 };
	//ctrl->add_dog_adoption(d);
	//SecondWindow w{ ctrl };
	//w.show();
	return a.exec();
}
