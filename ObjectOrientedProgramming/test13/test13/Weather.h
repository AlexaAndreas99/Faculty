#pragma once
#include <string>
class Weather
{
	int start;
	int end;
	double temp;
	int pp;
	std::string desc;
public:
	Weather();
	Weather(int,int,double,int,std::string);
	std::string toString();
	int get_pp() { return this->pp; }
	std::string get_desc() { return this->desc; }
	int get_start() { return this->start; }
	int get_end() { return this->end; }
	~Weather();
	friend std::istream & operator >>(std::istream & in, Weather & w);
};

