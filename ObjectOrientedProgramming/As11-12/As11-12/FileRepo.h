#pragma once
#include "Repo.h"
class FileRepo : public Repo {
protected:
	std::string source;
	// pure abstract methods used for writing and reading a file
	virtual void repoFromFile() = 0;
	virtual void repoToFile() = 0;

public:

	FileRepo(const std::string& source) : Repo(), source(source) {}

	FileRepo(const FileRepo& fl) : Repo(fl), source(fl.source) {}

	virtual	~FileRepo() = default;

	virtual void display() = 0;

};