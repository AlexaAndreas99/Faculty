#pragma once
#include "Except.h"
#include "Dog.h"
#include <vector>
class Repo
{
private:
	std::vector<Dog>* dogs;
	//DynamicVector<Dog> dogs;
public:
	Repo();
	~Repo();

	/*
	adds a dog to the repo
	input: Dog
	output: true if added, false if not
	*/
	bool add_dog(const Dog& d);
	/*
	removes a dog from the repo
	input:breed,name
	output: true if removed, false if not
	*/
	bool remove_dog(const std::string& name, const std::string& breed);
	/*
	finds a Dog by name and breed
	input: name,breed
	output: the dog that was found, or an empty dog
	*/
	Dog findByNameAndBreed(const std::string& name, const std::string& breed);
	/*
	finds the position of a dog in repo
	input: Dog
	output: its position
	*/
	int find_pos(const Dog &d);
	bool update(Dog odog, Dog ndog);
	std::vector<Dog>* get_all() { return dogs; }
	void save();
};

class RepoException :public Except {

public:
	RepoException(std::string msg) : Except(msg) {}
};