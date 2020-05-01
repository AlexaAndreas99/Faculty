#include "Controller.h"





bool Controller::add_team(std::string name, std::string country, int score)
{
	if (this->repo.search(name))
		return false;
	Domain t{ name,country,score };
	this->repo.add(t);
	return true;
}

bool Controller::win(std::string name1, std::string name2, std::string name3)
{
	if (this->repo.get_score(name1) != this->repo.get_score(name2))
		return false;
	this->repo.inc_score(name3);
	return true;
}

DynamicVector<Domain> Controller::sort()
{
	Domain aux;
	DynamicVector<Domain> dv = this->repo.get_dv();
	for (int i = 0; i < dv.get_size() - 1; i++)
		for (int j = i; j < dv.get_size(); j++)
			if (dv[i].get_score() < dv[j].get_score())
			{
				aux = dv[i];
				dv[i] = dv[j];
				dv[j] = aux;
			}
	return dv;
}

Controller::~Controller()
{
}
