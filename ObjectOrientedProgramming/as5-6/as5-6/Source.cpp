/*
#include <Windows.h>
#include <iostream>
#include <string>
#include "DynamicVector.h"
#include "Repo.h"
#include "Controller.h"
#include "Dog.h"
#include <crtdbg.h>
#include <assert.h>
#include <shellapi.h>
#include "UI.h"
#include <vector>
#include <fstream>
#include "CSVRepo.h"
#include "FileRepo.h"
#include "HTMLRepo.h"
using namespace std;
void start()
{
	string s;
	//Repo repo{}, adoption{};
	FileRepo* r = nullptr;
	FileRepo* a = nullptr;
	r = new CSVRepo("data.txt");
	cout << "csv or html?";
	cin >> s;
	if(s=="html")
		a = new HTMLRepo("file.html");
	else
		a = new CSVRepo("New Text Document.txt");
	Controller* ctrl=new Controller(r,a);
	UI* ui=new UI(ctrl);
	ui->run();
	delete ui;
}
int main()
{
	start();
	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}
*/
#include <QtWidgets/QApplication>

int main(int argc, char*argv[])
{
	QApplication a(argc, argv);
}
