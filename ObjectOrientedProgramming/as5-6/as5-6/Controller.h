#pragma once
#include "Repo.h"
#include "FileRepo.h"
class Controller
{
private:
	FileRepo *repo;
	FileRepo *adoption;

public:
	Controller(FileRepo* r, FileRepo* a)  {
		repo = r;
		adoption = a;
	};
	Controller(const Controller& c);
	~Controller();
	/*
	adds a dog to the dogs repo
	input:breed,name,photo,age
	output: true if added, false if not
	*/
	bool add_dog_repo(const std::string& breed, const std::string& name, const std::string&photo, const int& age);
	bool add_dog_repo2(Dog &d);
	bool remove_dog_adoption(const std::string& breed, const std::string & name);
	/*
	adds a dog to the adoption list
	input: Dog
	output: true if added,false if not
	*/
	bool add_dog_adoption(const Dog& d);
	/*
	removes a dog from the dogs repo
	input:breed,name
	output: true if removed, false if not
	*/
	bool remove_dog_repo(const std::string& breed, const std::string& name);
	/*
	updates a dog from the dogs repo
	input:breed,name,photo,age, new_name,new_photo
	output: true if updated, false if not
	*/
	bool update_dog_repo(const std::string& name, const std::string& breed, const std::string& photo, int age, const std::string& new_name, const std::string& new_photo);
	FileRepo* get_repo() const { return repo; }
	FileRepo* get_adoption() const { return adoption; }
};

