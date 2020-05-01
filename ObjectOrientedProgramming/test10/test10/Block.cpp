#include "Block.h"
#include <iostream>




Block::Block(std::string addres, int year, int ap, int oc)
{
	this->addres = addres;
	this->occap = oc;
	this->year = year;
	this->totalap = ap;
}

bool Block::mustBeRestored()
{
	int year = 2019 - this->year;
	double pr = (this->occap*100/this->totalap);
	//std::cout << pr<<std::endl;
	return pr>80&&year>40;
}

bool Block::canBeDemolished()
{
	double pr = (this->occap * 100 / this->totalap);
	return pr<5;
}

std::string Block::toString()
{
	std::string s= "Block: ";
	s += this->addres;
	s += "|";
	s += std::to_string(this->year);
	s += "|";
	s += std::to_string(this->totalap);
	s += "|";
	s += std::to_string(this->occap);
	s += "\n";
	return s;
}

int Block::get_year()
{
	return Building::get_year();
}

std::string Block::get_addres()
{
	return Building::get_addres();
}

Block::~Block()
{
}
