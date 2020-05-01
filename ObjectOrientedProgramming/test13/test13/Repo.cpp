#include "Repo.h"
#include <fstream>

Repo::Repo()
{
	this->load();
}

Repo::Repo(std::string f)
{
	this->file = f;
	this->load();

}

void Repo::add(Weather w)
{
	this->data.push_back(w);
}

void Repo::load()
{
	std::ifstream infile("data.txt");
	if (!infile.is_open())
		return;

	Weather w;
	while (infile >> w)
	{
		this->data.push_back(w);

	}
	infile.close();
}


Repo::~Repo()
{
}
