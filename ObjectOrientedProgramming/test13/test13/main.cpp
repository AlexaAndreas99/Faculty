#include "test13.h"
#include <QtWidgets/QApplication>
#include "Controller.h"
#include "Repo.h"
#include <assert.h>
void test_total()
{
	Repo r{ "test.txt" };
	Controller ctrl{ r };
	assert(ctrl.get_total("sunny") == 6);
	assert(ctrl.get_total("foggy") == 3);
	assert(ctrl.get_total("rainy") == 3);
	assert(ctrl.get_total("cloudy") == 3);
	assert(ctrl.get_total("sunnasdasdasy") == 0);

}
int main(int argc, char *argv[])
{
	test_total();
	QApplication a(argc, argv);
	Repo r{ "data.txt" };
	Controller ctrl{ r };
	test13 w{ ctrl };
	w.show();
	return a.exec();
}
