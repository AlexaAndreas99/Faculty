#include "Controller.h"




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

bool Controller::update_dog_repo(const std::string& name, const std::string& breed, const std::string& photo, int age, const std::string& new_name, const std::string& new_photo)
{
	Dog d = this->repo->findByNameAndBreed(name, breed);
	if (d.get_name() == "" || d.get_breed() == "")
		return false;
	Dog new_d = this->repo->findByNameAndBreed(new_name, breed);
	this->remove_dog_repo(breed, name);
	this->add_dog_repo(breed, new_name, new_photo, age);
	return true;
}