#include "CSVRepo.h"
#include <fstream>
#include <stdlib.h>

void CSVRepo::repoFromFile()
{
	std::ifstream infile(source);
	if (!infile.is_open())
		return;

	Dog d;
	while (infile >> d)
	{

		try {
			this->add_dog(d);

		}
		catch (RepoException& v) {
			std::cout << v.what() << std::endl;
		}
		catch (Except& v) {
			std::cout << v.what() << std::endl;
		}
	}
	infile.close();
}
void CSVRepo::repoToFile()
{
	std::ofstream myfile;
	myfile.open(source);
	std::vector<Dog>* dogs = this->get_all();
	for (auto &i : *dogs)
	{
		myfile << i << std::endl;
	}
	myfile.close();
}

CSVRepo::CSVRepo(const std::string & source) : FileRepo(source) {
	this->repoFromFile();
}

CSVRepo::~CSVRepo()
{
	this->repoToFile();
}

void CSVRepo::display()
{
	std::string s = "notepad \"" + source + "\"";
	system(s.c_str());
}

