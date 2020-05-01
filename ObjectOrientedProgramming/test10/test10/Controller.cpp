#include "Controller.h"
#include <iostream>
#include <fstream>


Controller::Controller()
{
}

void Controller::add(Building * b)
{
	this->repo.push_back(b);
}

std::vector<Building*> Controller::get_all()
{
	return this->repo;
}

std::vector<Building*> Controller::get_restored()
{
	std::vector<Building*> v,r=this->get_all();
	for (auto i : r)
		if (i->mustBeRestored())
			v.push_back(i);
	return v;
}

std::vector<Building*> Controller::get_demolished()
{
	std::vector<Building*> v, r = this->get_all();
	for (auto i : r)
		if (i->canBeDemolished())
			v.push_back(i);
	return v;
}

void Controller::write(std::string filename, std::vector<Building*>vect)
{
	std::ofstream myfile;
	myfile.open(filename);
	for (auto i : vect)
		myfile << i->toString();

	myfile.close();
}


Controller::~Controller()
{
}
