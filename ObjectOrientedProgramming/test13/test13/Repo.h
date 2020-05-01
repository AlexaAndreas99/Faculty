#pragma once
#include <vector>
#include "Weather.h"
class Repo
{
	std::vector<Weather> data;
	std::string file;
public:
	Repo();
	Repo(std::string f);
	void add(Weather w);
	void load();
	std::vector<Weather> get_all() { return this->data; }
	~Repo();
};

