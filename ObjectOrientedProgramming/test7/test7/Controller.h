#pragma once
#include "Repository.h"
#include <iostream>
class Controller
{
private:
	Repository repo;
public:
	Controller(Repository r) :repo{ r }{}
	/*
	adds a team to the repo
	input: name ,country,score
	output: true if added, false otherwise
	*/
	bool add_team(std::string name, std::string country,int score);
	Repository get_repo() { return this->repo; }
	bool win(std::string name1, std::string name2, std::string name3);
	
	/*
	return a sorted list of the teams
	input: None
	output: the sorted list
	*/
	DynamicVector<Domain> sort();
	~Controller();
};

