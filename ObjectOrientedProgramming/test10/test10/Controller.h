#pragma once
#include "Building.h"
#include <vector>
class Controller
{
private:
	std::vector<Building*> repo;
public:
	Controller();
	void add(Building* b);
	std::vector<Building*> get_all();
	std::vector<Building*> get_restored();
	std::vector<Building*> get_demolished();
	void write(std::string filename,std::vector<Building*>vect);

	~Controller();
};

