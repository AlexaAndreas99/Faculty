#pragma once
#include <iostream>
#include <Windows.h>
#include "Controller.h"
#include "Repository.h"
#include "DynamicVector.h"
#include "Domain.h"
class UI
{

private:
	Controller ctrl;
public:
	UI(Controller ctrl): ctrl{ctrl}{}
	void add();
	void print_all();
	void match();
	void set_up();
	void run();
	~UI();
};

