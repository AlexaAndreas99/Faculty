#pragma once
#include "Controller.h"
#include <iostream>
#include <vector>
class UI
{ private:
	Controller ctrl;
public:
	UI(Controller ctrl);
	void add();
	void menu();
	void run();
	void show();
	void show_restored();
	~UI();
};

