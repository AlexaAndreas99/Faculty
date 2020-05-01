#pragma once

#include "FileRepo.h"

// Comma Separate Value - repository -> writes and reads to a text file in CSV format
class CSVRepo : public FileRepo {
protected:
	void repoFromFile() override;
	void repoToFile() override;

public:

	CSVRepo(const std::string& source);
	~CSVRepo();
	void display() override;
};