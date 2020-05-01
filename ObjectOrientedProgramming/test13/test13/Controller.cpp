#include "Controller.h"
#include <exception>


Controller::Controller(Repo re)
{
	this->r = re;
}

void Controller::add(Weather w)
{
	this->r.add(w);
}


std::vector<Weather> Controller::get_filtered(std::string s)
{
	std::vector<Weather> v;
	std::vector<Weather> w = this->r.get_all();
	if (s == "")
		return w;
	//try {
		int pp = std::stoi(s);
		//throw exception();
		for (auto i : w)
			if (i.get_pp() < pp)
				v.push_back(i);
	//}

	return v;
}

int Controller::get_total(std::string s)
{
	int sum = 0;
	std::vector<Weather> w = this->r.get_all();
	for (auto i : w)
		if (i.get_desc() == s)
			sum += i.get_end() - i.get_start();
		
	return sum;
}

Controller::~Controller()
{
}
