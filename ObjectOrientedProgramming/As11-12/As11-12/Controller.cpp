#include "Controller.h"
#include <stdio.h>
#include <string.h>



Controller::Controller(const Controller & c)
{
	repo = c.repo;
	adoption = c.adoption;
}

Controller::~Controller()
{
	delete repo;
	delete adoption;
}

bool Controller::add_dog_repo(const std::string& breed, const std::string& name, const std::string&photo, const int& age)
{
	Dog d{ breed,name,photo,age };
	return this->repo->add_dog(d);
}

bool Controller::add_dog_repo2(Dog & d)
{
	return this->repo->add_dog(d);
}

bool Controller::remove_dog_adoption(const std::string & breed, const std::string & name)
{
	return this->adoption->remove_dog(name, breed);
}

bool Controller::add_dog_adoption(const Dog& d)
{
	return this->adoption->add_dog(d);
}
bool Controller::remove_dog_repo(const std::string& breed, const std::string& name)
{
	return this->repo->remove_dog(name, breed);
}

bool Controller::update_dog_repo(const std::string& name, const std::string& breed, const std::string& new_name, const std::string& new_photo)
{
	Dog d = this->repo->findByNameAndBreed(name, breed);
	if (d.get_name() == "" || d.get_breed() == "")
		return false;
	int age = d.get_age();
	std::string s = d.get_breed();
	Dog new_d = this->repo->findByNameAndBreed(new_name, breed);
	//this->remove_dog_repo(breed, name);
	//this->add_dog_repo(s, new_name, new_photo, age);
	return this->repo->update(d,new_d);
}

std::vector<Dog> Controller::filterByAge(std::string age)
{
	std::vector<Dog> filter;
	std::vector<Dog> dogs = *this->get_repo()->get_all();
	if (age == "")
	{
		for (auto i : dogs)
			filter.push_back(i);
		return filter;
	}
	try
	{
		int a = std::stoi(age);
		for (auto i : dogs)
			if (i.get_age() == a)
				filter.push_back(i);
	}
	catch (std::exception)
	{

	}
	return filter;
}

std::vector<Dog> Controller::filterByName(std::string str)
{


	std::vector<Dog> filter;
	std::vector<Dog> dogs = *this->get_repo()->get_all();
	if (str == "")
	{
		for (auto i : dogs)
			filter.push_back(i);
		return filter;
	}
	try
	{
		for (auto i : dogs)
			if (strstr(i.get_name().c_str(),str.c_str()))
				filter.push_back(i);
	}
	catch (std::exception)
	{

	}
	return filter;
}

std::vector<Dog> Controller::filterByBreedandAge(std::string str,int a)
{
	std::vector<Dog> filter;
	std::vector<Dog> doggos = *this->get_repo()->get_all();
	if (str == "")
	{
		for (auto i : doggos)
			if(i.get_age()<a)
				filter.push_back(i);
		return filter;
	}

	for (auto i : doggos)
		if (str==i.get_breed()&&i.get_age()<a)
			filter.push_back(i);
	return filter;
}
