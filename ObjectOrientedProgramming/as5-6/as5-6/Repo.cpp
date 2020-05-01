#include "Repo.h"

Repo::Repo()
{
	dogs = new std::vector<Dog>();
}

Repo::~Repo()
{
	delete dogs;
}

bool Repo::add_dog(const Dog& d)
{	
	Dog dog = findByNameAndBreed(d.get_name(), d.get_breed());
	if (dog.get_name() != "" || dog.get_breed() != "" || dog.get_photo() != "")
		throw RepoException("Cannot add dog: The given dog already exists!");
	this->dogs->push_back(d);
	this->save();
	return true;
}

Dog Repo::findByNameAndBreed(const std::string& name, const std::string& breed)
{
	for (auto &i : *(this->dogs))
	{
		if (i.get_breed() == breed && i.get_name() == name)
			return i;
	}
	return Dog{};
}

bool Repo::remove_dog(const std::string& name, const std::string& breed)
{
	Dog d = this->findByNameAndBreed(name, breed);
	if (d.get_name() == ""&&d.get_breed() == "")
		//throw RepoException("Cannot find the requested dog!");
		return false;
	int pos = this->find_pos(d);
	this->dogs->erase(dogs->begin()+pos);
	this->save();
	return true;
}

int Repo::find_pos(const Dog &d)
{
	/*
	for (int i = 0; i < this->dogs->size(); i++)
		if (*(this->dogs[i]).get_name() == d.get_name() && this->dogs[i].get_breed() == d.get_breed())
			return i; 
	*/
	int i = 0;
	for (auto &it : *(this->dogs))
	{
		if (it.get_name() == d.get_name() && it.get_breed() == d.get_breed())
			return i;
		i++;
	}
	return -1;
}

void Repo::save()
{

	std::ofstream myfile;
	myfile.open("data.txt");
	std::vector<Dog>* dogs = this->get_all();
	for (auto &i : *dogs)
	{
		myfile << i << std::endl;
	}
	myfile.close();
}
