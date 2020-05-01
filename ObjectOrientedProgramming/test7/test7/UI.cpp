#include "UI.h"



void UI::add()
{
	char name[50] ,country[50];
	std::cout << "----------Adding a team----------\n";
	std::cout << "Team name: ";
	std::cin >> name;
	std::cout << "Team country: ";
	std::cin >> country;

	if (this->ctrl.add_team(name, country, 0))
		std::cout << "Added succesfully\n";
	else
		std::cout << "Duplicate team added\n";
	

}

void UI::print_all()
{
	DynamicVector<Domain> dv = this->ctrl.get_repo().get_dv();
	
	dv=this->ctrl.sort();
	for (int i = 0; i < dv.get_size(); i++)
	{
		std::cout << dv[i].get_name().c_str()<<"|";
		std::cout << dv[i].get_country().c_str()<<"|";
		std::cout << dv[i].get_score();
		std::cout << std::endl;
	}

}

void UI::match()
{
	char name[50], name2[50],name3[50];
	std::cout << "----------Match time----------\n";
	std::cout << "First team name: ";
	std::cin >> name;
	std::cout << "Second team name: ";
	std::cin >> name2;
	std::cout << "Winning team name: ";
	std::cin >> name3;
	
	if (this->ctrl.win(name, name2, name3) == false)
		std::cout << "The selected teams cannot play\n";
	else
		this->ctrl.win(name, name2, name3);
}

void UI::set_up()
{
	this->ctrl.add_team("Larvik", "Norway", 0);
	this->ctrl.add_team("CSM", "Romania", 0);
	this->ctrl.add_team("HCM", "Montenegro", 0);
	this->ctrl.add_team("Rostov-Don", "Russia", 0);
	this->ctrl.add_team("FTC", "Hungary", 0);
}

void UI::run()
{
	char input;
	
	while (true)
	{	
		std::cout << "1.ADD TEAM\n";
		std::cout << "2.SHOW ALL TEAMS\n";
		std::cout << "3.PLAY MATCH\n";
		std::cout << "0.EXIT\n";
		std::cin >> input;
		if (input == '0')
			return;
		if (input == '1')
			this->add();
		if (input == '2')
			this->print_all();
		if (input == '3')
			this->match();
	}
}

UI::~UI()
{
}
