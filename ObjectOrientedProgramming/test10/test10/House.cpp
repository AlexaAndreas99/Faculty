#include "House.h"





House::House(std::string addres, int year, bool is, std::string type)
{
	this->addres = addres;
	this->year = year;
	this->isHistorical = is;
	this->type = type;
}

bool House::mustBeRestored()
{
	int year = 2019 - this->year;
	return year > 100;
}

bool House::canBeDemolished()
{
	return !this->isHistorical;
}

std::string House::toString()
{
	std::string s = "House: ";
	s += this->addres;
	s += "|";
	s += std::to_string(this->year);
	s += "|";
	s += this->type;
	s += "|";
	s += std::to_string(this->isHistorical);
	s += "\n";
	return s;
}

int House::get_year()
{
	return Building::get_year();
}

std::string House::get_addres()
{
	return Building::get_addres();
}


House::~House()
{
}
