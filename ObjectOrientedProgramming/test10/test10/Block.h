#pragma once
#include "Building.h"
#include <string>
class Block :
	public Building
{
private:
	int totalap;
	int occap;
public:
Block(std::string addres,int year,int ap,int oc);
bool mustBeRestored() override;
bool canBeDemolished() override;
std::string toString() override;
int get_year()override;
std::string get_addres() override;
~Block();
};

