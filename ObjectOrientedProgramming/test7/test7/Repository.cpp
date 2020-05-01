#include "Repository.h"



Repository::Repository()
{
}



bool Repository::add(Domain d)
{
	this->teams.add(d);
	return true;
}

bool Repository::search(std::string name)
{
	for(int i=0;i<this->teams.get_size();i++)
		if(this->teams[i].get_name()==name)
			return true;
	return false;
}

int Repository::get_score(std::string name)
{
	for (int i = 0; i < this->teams.get_size(); i++)
		if (this->teams[i].get_name() == name)
			return this->teams[i].get_score();
}

void Repository::inc_score(std::string name)
{

	for (int i = 0; i < this->teams.get_size(); i++)
		if (this->teams[i].get_name() == name)
			this->teams[i].set_score(this->teams[i].get_score() + 1);
}


Repository::~Repository()
{
}
