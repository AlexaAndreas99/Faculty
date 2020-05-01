#pragma once
#include <iostream>
class Domain
{
private:
	std::string name;
	std::string country;
	int score;
public:
	Domain();
	Domain(std::string name, std::string country, int score);
	std::string get_name() {return this->name;}
	std::string get_country() { return this->country; }
	int get_score() { return this->score; }
	void set_score(int score) { this->score = score; }
	~Domain();
};

