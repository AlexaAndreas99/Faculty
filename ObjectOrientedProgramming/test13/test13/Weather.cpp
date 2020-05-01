#include "Weather.h"
#include <vector>
#include <sstream>

Weather::Weather()
{
}

Weather::Weather(int s, int e, double t , int p , std::string d)
{
	this->desc = d;
	this->end = e;
	this->pp = p;
	this->start = s;
	this->temp = t;
}

std::string Weather::toString()
{
	return std::to_string(this->start) + "-" + std::to_string(this->end) + " | " + std::to_string(this->temp) + " | " + std::to_string(this->pp) + " | " + this->desc;
}

Weather::~Weather()
{
}

std::vector<std::string> tokenize(std::string str, char delimiter)
{
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string token;
	while (getline(ss, token, ','))
		result.push_back(token);
	return result;

}
std::istream & operator>>(std::istream & in, Weather & w)
{
		std::string line;
		getline(in, line);
		if (line.size() == 0)
			return in;
		std::vector<std::string> tokens = tokenize(line, ',');
		w.start = std::stoi(tokens[0]);
		w.end = std::stoi(tokens[1]);
		w.temp = std::stod(tokens[2]);
		w.pp = std::stoi(tokens[3]);
		w.desc = tokens[4];
		return in;	}


