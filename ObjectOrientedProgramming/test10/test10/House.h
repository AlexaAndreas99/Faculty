#pragma once
#include "Building.h"
class House :
	public Building
{
private:
	std::string type;
	bool isHistorical;
public:
	House(std::string addres,int year,bool is,std::string type);
	bool mustBeRestored() override;
	bool canBeDemolished() override;
	std::string toString() override;
	int get_year()override;
	std::string get_addres() override;

	~House();
};

