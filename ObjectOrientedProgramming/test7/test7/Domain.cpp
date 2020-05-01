#include "Domain.h"



Domain::Domain()
{
	this->country = "";
	this->name = "";
	this->score = 0;
}

Domain::Domain(std::string name, std::string country, int score)
{
	this->name = name;
	this->country = country;
	this->score = score;
}


Domain::~Domain()
{
}
