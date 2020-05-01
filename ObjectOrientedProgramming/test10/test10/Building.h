#pragma once
#include <string>
class Building
{
protected:
	std::string addres;
	int year;

public:
	virtual bool mustBeRestored() { return 1; }
	virtual bool canBeDemolished() { return 1; }
	virtual std::string toString() { return ""; }
	virtual int get_year() { return this->year; }
	virtual std::string get_addres() { return this->addres; }
	Building();
	~Building();
};

