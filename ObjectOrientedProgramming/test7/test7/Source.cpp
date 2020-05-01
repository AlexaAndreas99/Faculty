#include <iostream>
#include <Windows.h>
#include "Controller.h"
#include "Repository.h"
#include "UI.h"
#include <assert.h>

void add_test()
{
	Repository r{};
	Controller ctrl{ r };
	UI ui{ ctrl };
	ctrl.add_team("asd", "qwe", 0);
	DynamicVector<Domain> dv = ctrl.get_repo().get_dv();
	assert(dv.get_size() == 1);
	ctrl.add_team("asd", "qwe", 0);
	dv = ctrl.get_repo().get_dv();
	assert(dv.get_size() == 1);
}

void sort_test()
{
	Repository r{};
	Controller ctrl{ r };
	UI ui{ ctrl };
	ctrl.add_team("asd", "qwe", 0);
	ctrl.add_team("qwe", "asd", 0);
	ctrl.win("asd", "qwe", "qwe");
	DynamicVector<Domain> dv = ctrl.get_repo().get_dv();
	assert(dv[0].get_name() == "qwe");
}
int main()
{

	Repository r{};
	Controller ctrl{ r };
	UI ui{ ctrl };
	add_test();
	ui.set_up();
	ui.run();
	system("pause");
	return 0;
}