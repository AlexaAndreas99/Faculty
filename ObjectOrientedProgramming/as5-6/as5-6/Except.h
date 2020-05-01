#pragma once
#include <string>
#include <exception>
class Except:public std::exception
{
private:
	std::string msg;
public:
	Except(std::string msg):msg(msg){}
	const char* what()
	{
		return msg.c_str();
	}

};

