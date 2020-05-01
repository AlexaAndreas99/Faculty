#include "UI.h"
#include "Building.h"
#include "Block.h"
#include "House.h"


UI::UI(Controller ctrl)
{
	this->ctrl = ctrl;
}

void UI::add()
{
	std::string ad,type;
	int year,totalap,ocap;
	bool is;
	char i;
	Building* b = nullptr;
	std::cout << "1.Block\n";
	std::cout << "2.House\n";
	std::cin >> i;
	if (i == '1')
	{	
		std::cout << "addres: \n";
		std::cin >> ad;
		std::cout << "year: \n";
		std::cin >> year;
		std::cout << "total ap: \n";
		std::cin >> totalap;
		std::cout << "occupied ap: \n";
		std::cin >> ocap;
		b = new Block(ad, year, totalap, ocap);

	}
	else
	{
		std::cout << "addres: \n";
		std::cin >> ad;
		std::cout << "year: \n";
		std::cin >> year;
		std::cout << "type: \n";
		std::cin >> type;
		std::cout << "is Historical: \n";
		std::cin >> is;
		b = new House(ad, year, is, type);
	}
	this->ctrl.add(b);
}
void UI::menu()
{
	std::cout << "1.add a building\n";
	std::cout<<"2.show all buildings\n";
	std::cout << "3.show all buildings that must be restored\n";
	std::cout << "4.save\n";
	std::cout << "0.exit\n";

}

void UI::run()
{
	Building* b = nullptr;
	Building* h=nullptr;
	Building* a = nullptr;
	b = new Block("asd", 1900, 100, 90);
	this->ctrl.add(b);
	a = new Block("qwe", 1900, 100, 2);
	this->ctrl.add(a);
	h = new House("rty", 1800, 0, "duplex");
	this->ctrl.add(h);
	char input;
	this->menu();
	std::cin >> input;
	while (true)
	{
		if (input == '0')
			return;
		if (input == '1')
			this->add();
		if (input == '2')
			this->show();
		if (input == '3')
			this->show_restored();
		this->menu();
		if (input == '4')
		{
			this->ctrl.write("restore.txt", this->ctrl.get_restored());
			this->ctrl.write("demolish.txt", this->ctrl.get_demolished());
		}
		std::cin >> input;

	}
	
}

void UI::show()
{
	
	std::vector<Building*> v = this->ctrl.get_all();
	for (auto i : v)
		std::cout << i->toString();

}

void UI::show_restored()
{
	int year;
	std::string ad;
	std::cout << "year: \n";
	std::cin >> year;


	std::cout << "addres: \n";
	std::cin >> ad;
	std::vector<Building*>v = this->ctrl.get_restored();
	for (auto i : v)
		if(i->get_addres()==ad&&i->get_year()<year)
		std::cout << i->toString();
}


UI::~UI()
{
}
