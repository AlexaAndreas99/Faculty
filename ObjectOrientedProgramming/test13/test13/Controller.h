#pragma once
#include "Repo.h"
#include "Weather.h"
class Controller
{
private:
	Repo r;
public:
	Controller(Repo re);
	void add(Weather w);
	Repo get_repo() { return this->r; }
	std::vector<Weather> get_filtered(std::string s);
	/*
	get the total sum of the hours that match the description to s
	input: string s
	output: int sum
	*/
	int get_total(std::string s);
	~Controller();
};

