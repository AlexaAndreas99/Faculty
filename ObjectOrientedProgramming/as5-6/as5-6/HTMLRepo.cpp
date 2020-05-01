#include "HTMLRepo.h"
#include<Windows.h>
#include <shellapi.h>





void HTMLRepo::repoFromFile()
{
}

void HTMLRepo::repoToFile()
{
	std::ofstream myfile;
	std::string s = "<!DOCTYPE html>\n<html>\n<head>\n<title>Adoption</title>\n</head>\n<body>\n<table border = ""1"">\n<tr>\n<td>Name</td>\n<td>Breed</td>\n<td>Age</td>\n<td>Photo link</td>\n</tr>";
	std::string before = "<tr>", after = "</tr>", href = "<td><a href = ", bw = "<td>", aw = "</td>", link = ">Link</a></td>";
	std::string end = "</tr>\n</table>\n</body>\n</html>";
	myfile.open("file.html");

	std::vector<Dog>* dogs = this->get_all();
	myfile << s; 
	for (auto &i : *dogs)
	{
		myfile <<  before << std::endl << bw << i.get_name() << aw << std::endl << bw << i.get_breed() << aw << std::endl << bw << i.get_age() << aw << std::endl << href << std::endl << i.get_photo() << link << std::endl << after << std::endl ;

	}
	myfile << end;
	myfile.close();
}

HTMLRepo::HTMLRepo(const std::string & source) : FileRepo(source)
{
}

HTMLRepo::~HTMLRepo()
{
	this->repoToFile();
}

void HTMLRepo::display()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", "file:///C:/Users/Andreas-PC/source/repos/as5-6/as5-6/file.html", NULL, SW_SHOWMAXIMIZED);
}
