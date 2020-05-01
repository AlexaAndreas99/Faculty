#include "UI.h"
#include "Util.h"
#include "Comparator.h"
UI::UI(Controller * c)
{
	ctrl = c;
}
UI::~UI()
{
	delete ctrl;
}
void UI::dogTest()
{
	Dog d{ "Husky","Sparky","www",2 };
	Dog d1{};
	assert(d.get_age() == 2);
	assert(d.get_breed() == "Husky");
	assert(d.get_name() == "Sparky");
	assert(d.get_photo() == "www");
}

void UI::vectorTest()
{
	Dog* list;
	Dog d{ "Husky","Sparky","www",2 };
	DynamicVector<Dog> v;
	DynamicVector<Dog> dogs{ 1 };
	assert(v.get_size() == 0);
	list = v.getAll();
	dogs = dogs + d;
	v = d + dogs;
	assert(v[0].get_age() == 2);
	assert(dogs.get_size() == 2);
	dogs.add(d);
	assert(dogs.get_size() == 3);
	dogs.remove(1);
	assert(dogs.get_size() == 2);
	DynamicVector<Dog> v1{ dogs };
	v1.remove(-1);
}

void UI::repoTest()
{
	Repo repo{};
	Dog d{ "Husky","Sparky","www",2 };
	DynamicVector<Dog> dv;
	assert(repo.add_dog(d) == 1);
	assert(repo.add_dog(d) == 0);
	assert(repo.remove_dog("Spa", "sky") == 0);
	assert(repo.remove_dog("Sparky", "Husky") == 1);
	assert(repo.remove_dog("Sparky", "Husky") == 0);
}
/*
void UI::controllerTest()
{
	Repo repo{}, adoption{};
	Dog d{ "Husky","Sparky","www",2 };
	Controller ctrl{ repo, adoption };
	assert(ctrl.add_dog_adoption(d) == 1);
	assert(ctrl.add_dog_repo("asd", "qwe", "www", 2) == 1);
	assert(ctrl.add_dog_repo("asd", "qwe", "www", 2) == 0);
	assert(ctrl.update_dog_repo("qwe", "asd", "www", 2, "qwe", "www.dogs.com") == 1);
	assert(ctrl.update_dog_repo("zzz", "zzz", "www", 2, "qwe", "www.dogs.com") == 0);
	assert(ctrl.remove_dog_repo("asd", "qwe") == 1);
	assert(ctrl.remove_dog_repo("asd", "qwe") == 0);
	repo = ctrl.get_repo();
	repo = ctrl.get_adoption();
}
*/
void UI::testAll()
{
	dogTest();
	vectorTest();
	repoTest();
	//controllerTest();
}

void UI::print_all()
{
	std::vector<Dog>* dogs = this->ctrl->get_repo()->get_all();
	//Util utility;
	//comparator_by_age* cmp=new comparator_by_age();
	//utility.sort(*dogs, cmp);
	for (auto &i : *dogs)
	{
		cout << "Name: " << i.get_name().c_str() << '|';
		cout << " Breed: " << i.get_breed().c_str() << "|";
		cout << " Age: " << i.get_age() << "|";
		cout << " Photo: " << i.get_photo().c_str() << "\n";
	}
	//delete cmp;
}

void UI::set_up()

{
	this->ctrl->add_dog_repo("Yorkshire", "Kido", "https://imgur.com/a/d1ZRGQX", 4);
	this->ctrl->add_dog_repo("Chowchow", "Misha", "https://imgur.com/a/NhcFpiL", 2);
	this->ctrl->add_dog_repo("Chiuaua", "Merlin", "https://imgur.com/gallery/dNDYKMZ", 3);
	this->ctrl->add_dog_repo("Teckel", "Mimi", "https://imgur.com/gallery/6t6Q6MN", 1);
	this->ctrl->add_dog_repo("Labrador", "Zenda", "https://imgur.com/gallery/jCuqmYx", 2);
	this->ctrl->add_dog_repo("Bichon", "Oly", "https://imgur.com/gallery/AaYGNZb", 3);
	this->ctrl->add_dog_repo("German Shepherd", "Bruno", "https://imgur.com/t/german_shepherd/Vln2ZAg", 4);
	this->ctrl->add_dog_repo("Beagle", "Bigghy", "https://imgur.com/gallery/EdQs9jA", 2);
	this->ctrl->add_dog_repo("Yorkshire", "Ricky", "https://imgur.com/gallery/GxDTsRg", 2);
	this->ctrl->add_dog_repo("Yorkshire", "Oreo", "https://imgur.com/gallery/9TLrcyi", 1);

}

void UI::add()
{
	std::cout << "-----------------------" << "Adding dog" << "-----------------------" << "\n";
	int age;
	char  breed[50], name[50], photo[100];
	std::cout << "Name: ";
	std::cin >> name;

	std::cout << "\nBreed: ";
	std::cin >> breed;

	std::cout << "\nAge: ";
	std::cin >> age;

	std::cout << "\nPhoto: ";
	std::cin >> photo;

	try {
		if (this->ctrl->add_dog_repo(breed, name, photo, age))
			std::cout << "\nDog added succesfully!\n";
		
	}
	catch (RepoException& v) {
		cout << v.what() << std::endl;
	}
	catch (Except& v) {
		cout << v.what() << std::endl;
	}
}
void UI::print_adoptionList()
{

	std::vector<Dog>* dogs = this->ctrl->get_adoption()->get_all();
	for (auto &i : *dogs)

	{
		std::cout << "Name: " << i.get_name() << '|';
		std::cout << " Breed: " << i.get_breed() << "|";
		std::cout << " Age: " << i.get_age() << "\n";
	}
}

void UI::adopt_menu()
{
	std::cout << "\n0. Exit\n";
	std::cout << "1. Next dog\n";
	std::cout << "2. Adopt dog\n";

}

void UI::print_dog( Dog  d)
{
	std::cout << "Name: " << d.get_name() << '|';
	std::cout << " Breed: " << d.get_breed() << "|";
	std::cout << " Age: " << d.get_age() << "\n";

}

void UI::open(Dog d)
{
	ShellExecute(NULL, NULL, "chrome.exe", d.get_photo().c_str(), NULL, SW_SHOWMINIMIZED);
}


void UI::show_allDogs()
{
	system("cls");
	std::vector<Dog>* dogs = this->ctrl->get_repo()->get_all();
	int i = 0, input;

		for(auto it=dogs->begin();true;it++)
		{
			if (it == dogs->end())
				it = dogs->begin();

			this->print_dog(*it);
			//this->open(*it);
			adopt_menu();
			std::cin >> input;
			system("cls");
			if (input == 0)
				return;
			if (input == 2)
			{
				try {
					if (this->ctrl->add_dog_adoption(*it))
						std::cout << "Dog added succesfuly to the adoption list!";
				}
				catch (RepoException& v) {
					cout << v.what() << std::endl;
				}
				catch (Except& v) {
					cout << v.what() << std::endl;
				}
			}
	}
	
}
/*
void UI::show_dogsByBreed()
{
	std::vector<Dog> dogs = this->ctrl.get_repo().get_all();
	int i = 0, age, input;
	std::cout << "Breed: ";
	std::string breed;
	if (getchar())
		i++;
	i--;
	getline(std::cin, breed);

	std::cout << "Maximum age: ";
	std::cin >> age;
	system("cls");
	while (true)
	{
		if ((breed == "" || dogs[i].get_breed() == breed) && age >= dogs[i].get_age())
		{
			std::cout << "Name: " << dogs[i].get_name() << '|';
			std::cout << " Breed: " << dogs[i].get_breed() << "|";
			std::cout << " Age: " << dogs[i].get_age() << "\n";
			//ShellExecute(NULL, NULL, "chrome.exe", dogs[i].get_photo().c_str(), NULL, SW_SHOWMINIMIZED);
		}
		adopt_menu();
		std::cin >> input;
		system("cls");
		if (input == 0)
			return;
		if (input == 1)
		{
			if (i + 1 == dogs.size())
				i = 0;
			else
				i++;
			while (dogs[i].get_breed() != breed && breed != "")
				if (i == dogs.size())
					i = 0;
				else
					i++;
		}

		if (input == 2)
			if (this->ctrl.add_dog_adoption(dogs[i]) == 0)
				std::cout << "Already added to the adoption list!\n";
			else
				std::cout << "Dog added to the adoption list!\n";

		if (i == dogs.size())
			i = 0;

	}
	
}
*/
void UI::menu()
{
	std::cout << "\n0. Exit\n";
	std::cout << "1. Add dog\n";
	std::cout << "2. Delete dog\n";
	std::cout << "3. Update dog\n";
	std::cout << "4. Show all dogs\n";

}

void UI::user_menu()
{
	std::cout << "\n0. Exit\n";
	std::cout << "1. Show all dogs\n";
	std::cout << "2. Show all the dogs by a given breed and age\n";
	std::cout << "3. Show the adoption list\n";
	std::cout << "4. Delete a dog from the adoption list\n";
	std::cout << "5. Open the adoption list\n";

}

void UI::remove()
{
	std::cout << "-----------------------" << "Removing dog" << "-----------------------" << "\n";
	char breed[50], name[50];
	std::cout << "Name: ";
	std::cin >> name;

	std::cout << "\nBreed: ";
	std::cin >> breed;

	try {
		if (this->ctrl->remove_dog_repo(breed, name))
			std::cout << "\nDog removed succesfully!\n";
	}
	catch (RepoException& r) {
		cout << r.what() << std::endl;
	}
}
void UI::remove_adoption()
{
	std::cout << "-----------------------" << "Removing dog" << "-----------------------" << "\n";
	char breed[50], name[50];
	std::cout << "Name: ";
	std::cin >> name;

	std::cout << "\nBreed: ";
	std::cin >> breed;

	try {
		if (this->ctrl->remove_dog_adoption(breed, name))
			std::cout << "\nDog removed succesfully!\n";
	}
	catch (RepoException& r) {
		cout << r.what() << std::endl;
	}
}
void UI::update()
{
	std::cout << "-----------------------" << "Updating dog" << "-----------------------" << "\n";
	int age;
	char  breed[50], name[50], photo[100], new_name[50], new_photo[100];
	std::cout << "Name: ";
	std::cin >> name;

	std::cout << "\nNew name: ";
	std::cin >> new_name;

	std::cout << "\nBreed: ";
	std::cin >> breed;

	std::cout << "\nAge: ";
	std::cin >> age;

	std::cout << "\nPhoto: ";
	std::cin >> photo;

	std::cout << "\nNew photo: ";
	std::cin >> new_photo;

	if (this->ctrl->update_dog_repo(name, breed, photo, age, new_name, new_photo))
		std::cout << "\nDog updated succesfully!\n";
	else
		std::cout << "Cannot update dog\n";

}

void UI::run()
{
	//set_up();
	char input;

	std::cout << "1. Administrator mode" << "\n";
	std::cout << "2. User mode" << "\n";
	while (true)
	{
		std::cin >> input;
		if (input == '1')
		{
			while (true)
			{
				menu();
				std::cin >> input;
				if (input == '1')
				{
					add();

				}
				if (input == '4')
				{
					print_all();
				}
				if (input == '0')
				{
					return;
				}
				if (input == '2')
				{
					remove();
				}
				if (input == '3')
				{
					update();
				}
			}

		}
		if (input == '2')
		{
			while (true)
			{
				user_menu();
				std::cin >> input;
				if (input == '0')
					return;
				
				if (input == '1')
					show_allDogs();
				/*
				if (input == '2')
					show_dogsByBreed();
				*/
				if (input == '3')
					print_adoptionList();
				if (input == '4')
					this->remove_adoption();
				if (input == '5') {
					this->ctrl->get_adoption()->display();
					return;
				}
			}
		}
	}
	this->save();
}

void UI::save()
{
	std::ofstream myfile;
	myfile.open("data.txt");
	std::vector<Dog>* dogs = this->ctrl->get_repo()->get_all();
	for (auto &i : *dogs)
	{
		myfile << i<< std::endl;
	}
	myfile.close();
}

void UI::load()
{
	/*
	int k=0,ag;
	std::string age,line,breed,name,photo;
	std::ifstream myfile;
	std::vector<std::string> tokens;
	myfile.open("data.txt");
	while (getline(myfile, line, ','))
	{
		tokens.push_back(line);
	}
	for (auto i : tokens)
	{
		
		if (k == 0)
			name = i;
		if (k == 1)
			breed = i;
		if (k == 2)
			age = i;
		if (k == 3)
		{
			photo = i;
			k = -1;
			this->ctrl.add_dog_repo(breed, name, photo, std::stoi(age));
		}
		k++;
	}
	myfile.close();
	*/
	std::ifstream infile("data.txt");
	//infile.open("data.txt");
	if (!infile.is_open())
		return;

	Dog d;
	while (infile >> d)
	{
		
		try {
			this->ctrl->add_dog_repo2(d);
		
		}
		catch (RepoException& v) {
			cout << v.what() << std::endl;
		}
		catch (Except& v) {
			cout << v.what() << std::endl;
		}
	}
	infile.close();
}
