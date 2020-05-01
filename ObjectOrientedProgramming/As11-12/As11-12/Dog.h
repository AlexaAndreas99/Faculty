#pragma once
#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <shellapi.h>
class Dog
{
private:
	std::string breed;
	std::string name;
	std::string photo;
	int age;
public:
	Dog();
	Dog(const std::string& breed, const std::string& name, const std::string&photo, const int& age);
	~Dog();

	std::string get_name() const { return name; }
	std::string get_breed() const { return breed; }
	std::string get_photo() const { return photo; }
	std::string toString();
	std::string show();
	void open();
	int get_age() const { return age; }
	friend std::istream & operator >>(std::istream & in, Dog & d);
	friend std::ostream & operator <<(std::ostream & out, const Dog& d);
};

