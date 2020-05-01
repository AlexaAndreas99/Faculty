#include "Dog.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <shellapi.h>

Dog::Dog() :breed(""), name(""), photo(""), age(0) {}
Dog::Dog(const std::string& breed, const std::string& name, const std::string&photo, const int& age)
{
	this->age = age;
	this->name = name;
	this->breed = breed;
	this->photo = photo;
}

Dog::~Dog()
{
}

std::string Dog::toString()
{
	return this->name+" | "+this->breed+" | "+std::to_string(this->age)+" | "+this->photo;
}

std::string Dog::show()
{
	return "Name: "+this->name + "\n" + "Breed: "+this->breed + "\n" +"Age: "+ std::to_string(this->age) + "\n"+"Photo: " + this->photo;
}

void Dog::open()
{
	//ShellExecute(NULL, NULL, "chrome.exe", photo.c_str(), NULL, SW_SHOWMINIMIZED);
	ShellExecuteA(NULL, NULL, "chrome.exe", this->photo.c_str(), NULL, SW_SHOWMINIMIZED);
}


Dog create_dog(std::string s1, std::string s2, std::string s3, std::string s4)
{
	Dog d{ s2,s1,s4,std::stoi(s3) };
	return d;
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
std::string trim(const std::string& s)
{
	std::string result(s);
	size_t pos = result.find_first_not_of(' ');
	if (pos != -1)
		result.erase(0, pos);
	pos = result.find_last_not_of(' ');
	if (pos != std::string::npos)
		result.erase(pos + 1);

	return result;
}


std::istream & operator>>(std::istream & in, Dog & d)
{
	std::string line;
	getline(in, line);
	if (line.size() == 0)
		return in;
	std::vector<std::string> tokens = tokenize(line, ',');
	d = create_dog(trim(tokens[0]), trim(tokens[1]), trim(tokens[2]), trim(tokens[3]));
	return in;
}

std::ostream & operator<<(std::ostream & out, const Dog & d)
{
	out << d.get_name().c_str() << "," << d.get_breed().c_str() << "," << d.get_age() << "," << d.get_photo().c_str();
	return out;
}
