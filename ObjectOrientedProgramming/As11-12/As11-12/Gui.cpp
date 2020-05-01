#include "Gui.h"
#include <sstream>
#include "As1112.h"
#include <QtWidgets/QApplication>
#include <qshortcut.h>
Gui::Gui(Controller* c, QWidget* parent) :ctrl(c), QWidget{ parent }
{
	this->init();
	this->dogs = *this->ctrl->get_repo()->get_all();
	this->populate();
	
	model = new DogModel{ c->get_adoption() };
	//this->DogsListWidget->setModel(this->model);
	QSortFilterProxyModel* proxyModel =
		new QSortFilterProxyModel{};
	proxyModel->setSourceModel(this->model);
	this->adoptionView->setSortingEnabled(true);
	this->adoptionView->setModel(proxyModel);
	this->adoptionView->resizeColumnsToContents();



	this->iteratedDogs = this->ctrl->filterByBreedandAge("",99);
	QString listItem = QString::fromStdString(iteratedDogs[0].show());
	QListWidgetItem* listItemWidget = new QListWidgetItem(listItem);
	this->current->addItem(listItemWidget);
	this->currentDog = 0;
}


Gui::~Gui()
{
	delete ctrl;
}

void Gui::init()
{
	//layout
	QHBoxLayout* layout = new QHBoxLayout{ this };


	QWidget* leftW = new QWidget{};
	QVBoxLayout* leftSide = new QVBoxLayout{ leftW };
	this->filterText = new QLineEdit{};
	//list
	this->DogsListWidget = new QListWidget{};
	this->repoView = new QTableView{};

	//DogsListWidget->setStyleSheet("* {color: qlineargradient(spread:pad, x1:0 y1:0, x2:1 y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
	//	"background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 cyan, stop:1 blue);}");
	//model
	this->DogsListWidget->setSelectionMode(QAbstractItemView::SingleSelection);

	//dog form
	QWidget* dogsDataWidget = new QWidget{};
	QFormLayout* formLayout = new QFormLayout{ dogsDataWidget };
	this->nameInput = new QLineEdit{};
	//this->nameInput->setClearButtonEnabled(true);
	this->breedInput = new QLineEdit{};
	this->ageInput = new QLineEdit{};
	this->sourceInput = new QLineEdit{};
	this->newSourceInput = new QLineEdit{};
	this->newNameInput = new QLineEdit{};
	formLayout->addRow(new QLabel{ "Add:" });
	formLayout->addRow("&Name:", nameInput);
	formLayout->addRow("&Breed", breedInput);
	formLayout->addRow("&Age", ageInput);
	formLayout->addRow("&Source", sourceInput);
	formLayout->addRow(new QLabel{ "Update:" });
	formLayout->addRow("&New name", newNameInput);
	formLayout->addRow("&New source", newSourceInput);
	

	//buttons
	QWidget* buttonsWidget = new QWidget{};
	QGridLayout* gridLayout = new QGridLayout{ buttonsWidget };
	this->addButton = new QPushButton("Add a dog");
	this->deleteButton = new QPushButton("Delete a dog");
	this->UpdateButton = new QPushButton("Update a dog");
	this->undoButton = new QPushButton("Undo");
	this->redoButton = new QPushButton("Redo");
	gridLayout->addWidget(addButton, 0, 0);
	gridLayout->addWidget(deleteButton, 0, 1);
	gridLayout->addWidget(UpdateButton, 0, 2);
	gridLayout->addWidget(undoButton, 1, 0);
	gridLayout->addWidget(redoButton, 1, 1);
	//add to left
	leftSide->addWidget(new QLabel{"Dogs"});
	leftSide->addWidget(this->filterText);
	leftSide->addWidget(DogsListWidget);
	//leftSide->addWidget(this->repoView);
	leftSide->addWidget(dogsDataWidget);
	leftSide->addWidget(buttonsWidget);
	
	//middle
	
	QWidget* middleW = new QWidget{};
	QVBoxLayout* middleSide = new QVBoxLayout{ middleW };
	current = new QListWidget{};
	//this->current->setFixedHeight(200);

	//buttons
	QWidget* iteratorButtonsWidget = new QWidget{};
	QGridLayout* iteratorButtonsLayout = new QGridLayout{iteratorButtonsWidget };
	this->filterButton = new QPushButton{ "&Filter" };
	this->nextButton = new QPushButton{ "&Next" };
	this->adoptButton = new QPushButton{ "&Adopt" };
	this->openButton = new QPushButton{ "&Open" };
	this->newWindowButton = new QPushButton{ "&Open Adoption" };
	//openButton->setStyleSheet("* {color: qlineargradient(spread:pad, x1:0 y1:0, x2:1 y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
	//	"background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 white, stop:1 black);}");

	iteratorButtonsLayout->addWidget(this->filterButton, 0, 0);
	iteratorButtonsLayout->addWidget(this->openButton, 1, 0);
	iteratorButtonsLayout->addWidget(this->nextButton, 2, 0);
	iteratorButtonsLayout->addWidget(this->adoptButton, 3, 0);
	iteratorButtonsLayout->addWidget(this->newWindowButton, 4, 0);

	//filter form
	QWidget* iteratedDogsDataWidget = new QWidget{};
	QFormLayout* formLayout1 = new QFormLayout{ iteratedDogsDataWidget };
	this->breedFilterInput = new QLineEdit{};
	this->breedFilterInput->setClearButtonEnabled(true);
	this->ageFilterInput = new QLineEdit{};
	this->ageFilterInput->setClearButtonEnabled(true);
	formLayout1->addRow(new QLabel{ "Filter:" });
	formLayout1->addRow("&Breed:", breedFilterInput);
	formLayout1->addRow("&Age", ageFilterInput);



	middleSide->addWidget(new QLabel{ "Current dog" });
	middleSide->addWidget(current);
	middleSide->addWidget(iteratedDogsDataWidget);
	middleSide->addWidget(iteratorButtonsWidget);

	//right
	QWidget* rightW = new QWidget{};
	QVBoxLayout* rightSide = new QVBoxLayout{ rightW };
	adoption = new QListWidget{};

	//buttons
	QWidget* adoptionButtonsWidget = new QWidget{};
	QHBoxLayout* adoptionButtonsLayout = new QHBoxLayout{ adoptionButtonsWidget };
	this->openAdoptionButton = new QPushButton{ "&Open" };
	adoptionButtonsLayout->addWidget(this->openAdoptionButton);

	this->adoptionView = new QTableView{};

	/*
	rightSide->addWidget(new QLabel{ "Adoption list" });
	rightSide->addWidget(adoptionView);
	rightSide->addWidget(adoptionButtonsWidget);
	*/
	layout->addWidget(leftW);
	layout->addWidget(middleW);
	layout->addWidget(rightW);

	this->connectSignalAndSlots();
}

void Gui::populate()
{
	if (DogsListWidget->count() != 0)
		DogsListWidget->clear();
	for (auto i : dogs)
	{
		QString listItem = QString::fromStdString(i.toString());
		QListWidgetItem* listItemWidget = new QListWidgetItem(listItem);
		this->DogsListWidget->addItem(listItemWidget);
	}
	if (dogs.size() > 0)
		DogsListWidget->setCurrentRow(0);
}

int Gui::getDogIndex()
{
	return 0;
}

void Gui::moveDogToAdoption()
{	
	try
	{
		
		this->ctrl->add_dog_adoption(this->dogs[this->currentDog]);
		//QString listItem = QString::fromStdString(this->dogs[this->currentDog].toString());
		//QListWidgetItem* listItemWidget = new QListWidgetItem(listItem);
		//this->adoption->addItem(listItemWidget);
		
		//model->addDogToRepository(this->dogs[this->currentDog]);
		//this->sec->add(this->dogs[this->currentDog]);
	}
	catch (RepoException& v)
	{
		std::cout << v.what();
		QMessageBox msgBox;
		msgBox.critical(0, "Error", "Dog already added to the adoption list!");

	}
}

void Gui::deleteDog()
{
	try
	{
		int i=this->DogsListWidget->currentIndex().row();
		/*
		std::string name = nameInput->text().toStdString();
		std::string breed = breedInput->text().toStdString();
		if (name == "")
			throw exception("The name field must be populated!");
		if (breed == "")
			throw exception("The breed field must be populated!");
		*/
		Dog d = this->ctrl->get_repo()->findByNameAndBreed(dogs[i].get_name(), dogs[i].get_breed());
		this->ctrl->remove_dog_repo(dogs[i].get_breed(),dogs[i].get_name());
		dogs = *this->ctrl->get_repo()->get_all();
		this->populate();
		std::unique_ptr<Action> action{ new RemoveAction{ this->ctrl->get_repo(),d } };
		undoActions.push_back(std::move(action));
		redoActions.clear();

	}
	catch (RepoException& v)
	{
		std::cout << v.what();
		QMessageBox msgBox;
		msgBox.critical(0, "Error", "Cannot add element!");
	}
	catch (exception& v)
	{
		std::cout << v.what();
		QMessageBox msgBox;
		msgBox.critical(0, "Error", v.what());
	}
	
}

void Gui::moveAllDogs()
{
}

void Gui::addNewDog()
{
	try
	{

		std::string name = nameInput->text().toStdString();
		std::string breed = breedInput->text().toStdString();
		std::string a = ageInput->text().toStdString();
		std::string photo = sourceInput->text().toStdString();
		if (name == "")
			throw exception("The name field must be populated!");
		if (breed == "")
			throw exception("The breed field must be populated!");
		if (a == "")
			throw exception("The age field must be populated!");
		if (photo == "")
			throw exception("The source field must be populated!");

		int age = std::stoi(a);
		Dog d{ breed,name,photo,age };
		ctrl->add_dog_repo2(d);
		dogs = *this->ctrl->get_repo()->get_all();
		this->populate();
		std::unique_ptr<Action> action{ new AddAction{ this->ctrl->get_repo(),d } };
		undoActions.push_back(std::move(action));
		redoActions.clear();

		//model->addDogToRepository(d);
		this->nameInput->clear();
		this->breedInput->clear();
		this->ageInput->clear();
		this->sourceInput->clear();
	}
	catch (RepoException& v)
	{
		std::cout << v.what();
		QMessageBox msgBox;
		msgBox.critical(0, "Error", "Cannot add element!");
	}
	catch (exception& v)
	{
		std::cout << v.what();
		QMessageBox msgBox;
		msgBox.critical(0, "Error", v.what());

	}
	
}

void Gui::filterDogs()
{
	QString filter = this->filterText->text();
	std:vector<Dog> newList = this->ctrl->filterByName(filter.toStdString());
	if (DogsListWidget->count() != 0)
		DogsListWidget->clear();
	for (auto i : newList)
	{
		QString listItem = QString::fromStdString(i.toString());
		QListWidgetItem* listItemWidget = new QListWidgetItem(listItem);
		this->DogsListWidget->addItem(listItemWidget);
	}
	if (dogs.size() > 0)
		DogsListWidget->setCurrentRow(0);


}

void Gui::updateDog()
{
	try
	{
		int i = this->DogsListWidget->currentIndex().row();
		/*
		std::string name = nameInput->text().toStdString();
		std::string breed = breedInput->text().toStdString();
		*/
		std::string new_name = newNameInput->text().toStdString();
		std::string photo = newSourceInput->text().toStdString();
		/*
		if (name == "")
			throw exception("Please populate the name and the breed fields in order to find the dog!");
		if (breed == "")
			throw exception("Please populate the name and the breed fields in order to find the dog!");
		*/
		if (new_name == ""&&photo == "")
			throw exception("The new name or the new source field must be populated!");
		
		this->ctrl->update_dog_repo(this->dogs[i].get_name(), this->dogs[i].get_breed(), new_name, photo);
		dogs = *this->ctrl->get_repo()->get_all();
		this->populate();

	}
	catch (RepoException& v)
	{
		std::cout << v.what();
		QMessageBox msgBox;
		msgBox.critical(0, "Error", "Cannot add element!");
	}
	catch (exception& v)
	{
		std::cout << v.what();
		QMessageBox msgBox;
		msgBox.critical(0, "Error", v.what());

	}
	newNameInput->clear();
	newSourceInput->clear();
}

void Gui::next()
{

	if (this->currentDog == iteratedDogs.size()-1)
		this->currentDog = 0;
	else
		this->currentDog++;
	this->current->clear();
	QString listItem = QString::fromStdString(iteratedDogs[this->currentDog].show());
	QListWidgetItem* listItemWidget = new QListWidgetItem(listItem);
	this->current->addItem(listItemWidget);


}

void Gui::open()
{
	this->dogs[this->currentDog].open();
}

void Gui::openAdoption()
{
	this->ctrl->get_adoption()->display();
}

void Gui::iteratedFilter()
{
	try {
		std::string age = ageFilterInput->text().toStdString();
		std::string breed = breedFilterInput->text().toStdString();

		if (age == "")
			this->iteratedDogs = this->ctrl->filterByBreedandAge(breed, 999);
		else
		{
			int a = std::stoi(age);
			this->iteratedDogs = this->ctrl->filterByBreedandAge(breed, a);
		}
		this->current->clear();
		if (iteratedDogs.size() == 0)
			throw exception("No dogs match the requested filter!");
		
		QString listItem = QString::fromStdString(iteratedDogs[0].show());
		QListWidgetItem* listItemWidget = new QListWidgetItem(listItem);
		this->current->addItem(listItemWidget);
		this->currentDog = 0;
	}
	catch (exception& v)
	{
		std::cout << v.what();
		QMessageBox msgBox;
		msgBox.critical(0, "Error", v.what());

	}
}

void Gui::undo()
{
	/*
	model->undo();
	repoView->reset();
	*/
	if (undoActions.empty())
	{
		//throw RepositoryException{ "There are no more actions to undo." };
		return;
	}

	try
	{
		//undoActions.back()->executeUndo();
		std::unique_ptr<Action> last = std::move(undoActions.back());
		last->undo();

		undoActions.pop_back();
		redoActions.push_back(std::move(last));
		this->dogs = *this->ctrl->get_repo()->get_all();
		this->populate();

	}
	catch (RepoException& e)
	{
		//cout << e.what() << endl;
	}
}

void Gui::redo()
{
	if (redoActions.empty())
	{
		//throw RepositoryException{ "There are no more actions to undo." };
		return;
	}

	try
	{
		//undoActions.back()->executeUndo();
		std::unique_ptr<Action> last = std::move(redoActions.back());
		last->redo();

		redoActions.pop_back();
		undoActions.push_back(std::move(last));
		this->dogs = *this->ctrl->get_repo()->get_all();
		this->populate();


	}
	catch (RepoException& e)
	{
		//cout << e.what() << endl;
	}
}

void Gui::new_window()
{
	//hide();
	//As1112 w=new As1112();
	//NewWindow *nw = new NewWindow();
	//w.show();
	//this->hide();
	this->sec = new SecondWindow(this->ctrl);
	sec->show();
}

void Gui::connectSignalAndSlots()
{
	QObject::connect(this->addButton, &QPushButton::clicked, this, &Gui::addNewDog);
	QObject::connect(this->filterText, &QLineEdit::textChanged, this, &Gui::filterDogs);
	QObject::connect(this->deleteButton, &QPushButton::clicked, this, &Gui::deleteDog);
	QObject::connect(this->UpdateButton, &QPushButton::clicked, this, &Gui::updateDog);
	QObject::connect(this->nextButton, &QPushButton::clicked, this, &Gui::next);
	QObject::connect(this->openButton, &QPushButton::clicked, this, &Gui::open);
	QObject::connect(this->adoptButton, &QPushButton::clicked, this, &Gui::moveDogToAdoption);
	QObject::connect(this->openAdoptionButton, &QPushButton::clicked, this, &Gui::openAdoption);
	QObject::connect(this->filterButton, &QPushButton::clicked, this, &Gui::iteratedFilter);
	QObject::connect(this->undoButton, &QPushButton::clicked, this, &Gui::undo);
	QObject::connect(this->redoButton, &QPushButton::clicked, this, &Gui::redo);
	QObject::connect(this->newWindowButton, &QPushButton::clicked, this, &Gui::new_window);
	//QShortcut *sc = new QShortcut (QKeySequence("Ctrl+Z"), parent );

}
void Gui::keyPressEvent(QKeyEvent* event)
{
	QWidget::keyPressEvent(event);
	int k = event->key();

	if (QGuiApplication::keyboardModifiers() == Qt::ControlModifier)
	{
		switch (k) {
		case Qt::Key_Z:
			this->undo();
			break;

		case Qt::Key_Y:
			this->redo();
			break;
		}
	}
}