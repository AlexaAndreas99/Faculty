
#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include "DynamicVector.h"
#include "Repo.h"
#include "Controller.h"
#include "Dog.h"
#include <assert.h>
class UI
{
	Controller* ctrl;
public:
	UI(Controller * c);
	~UI();

	void dogTest();
	void vectorTest();
	void repoTest();
	//void controllerTest();
	void testAll();
	void print_all();
	void set_up();
	void add();
	void print_adoptionList();
	void adopt_menu();
	void print_dog( Dog d);
	void open(Dog d);
	void show_allDogs();
	/*
	void show_dogsByBreed();
	*/
	void menu();
	void user_menu();
	void remove();
	void remove_adoption();
	void update();
	void run();
	void save();
	void load();
};

