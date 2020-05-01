#pragma once
#include "FileRepo.h"
class HTMLRepo : public FileRepo {
protected:
	void repoFromFile() override;
	void repoToFile() override;

public:

	HTMLRepo(const std::string& source);
	~HTMLRepo();
	void display() override;
};

