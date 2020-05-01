#pragma once
#include "DynamicVector.h"
#include "Domain.h"
class Repository
{	
private:
	DynamicVector<Domain> teams;
public:
	Repository();
	/*
	adds a team to the dv
	input: a team
	output: true if added,false otherwise
	*/
	bool add(Domain d);
	DynamicVector<Domain> get_dv() { return this->teams; }
	bool search(std::string name);
	int get_score(std::string name);
	void inc_score(std::string name);
	~Repository();
};

