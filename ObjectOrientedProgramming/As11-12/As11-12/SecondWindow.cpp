#include "SecondWindow.h"


SecondWindow::SecondWindow(Controller* c, QWidget *parent)
	: ctrl(c), QWidget{ parent }
{
	this->init();
	//this->populate();
	
	
	model = new DogModel{ c->get_adoption() };
	//this->DogsListWidget->setModel(this->model);
	QSortFilterProxyModel* proxyModel =
		new QSortFilterProxyModel{};
	proxyModel->setSourceModel(this->model);
	this->adoptionView->setSortingEnabled(true);
	this->adoptionView->setModel(proxyModel);
	this->adoptionView->resizeColumnsToContents();
}

void SecondWindow::init()
{
	
	QHBoxLayout* layout = new QHBoxLayout{ this };
	QWidget* rightW = new QWidget{};
	QVBoxLayout* rightSide = new QVBoxLayout{ rightW };
	adoption = new QListWidget{};

	//buttons
	//QWidget* adoptionButtonsWidget = new QWidget{};
	//QHBoxLayout* adoptionButtonsLayout = new QHBoxLayout{ adoptionButtonsWidget };
//	this->openAdoptionButton = new QPushButton{ "&Open" };
//	adoptionButtonsLayout->addWidget(this->openAdoptionButton);

	this->adoptionView = new QTableView{};

	rightSide->addWidget(new QLabel{ "Adoption list" });
	rightSide->addWidget(adoptionView);
	//rightSide->addWidget(adoptionButtonsWidget);
	
	QWidget* leftW = new QWidget{};
	QVBoxLayout* leftSide = new QVBoxLayout{ leftW };


	QWidget* middleW = new QWidget{};
	QVBoxLayout* middleSide = new QVBoxLayout{ middleW };

	layout->addWidget(leftW);
	layout->addWidget(middleW);
	layout->addWidget(rightW);
	
	/*
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
	leftSide->addWidget(new QLabel{ "Dogs" });
	leftSide->addWidget(this->filterText);
	leftSide->addWidget(DogsListWidget);
	//leftSide->addWidget(this->repoView);
	leftSide->addWidget(dogsDataWidget);
	leftSide->addWidget(buttonsWidget);

	//middle
	/*
	QWidget* middleW = new QWidget{};
	QVBoxLayout* vLayoutMiddle = new QVBoxLayout{ middleW };
	this->moveOneButton = new QPushButton{ ">" };
	this->moveAllButton = new QPushButton{ ">>" };
	QWidget* uPart = new QWidget;
	QWidget* lPart = new QWidget;

	QWidget* midW = new QWidget{};
	QVBoxLayout* midSide = new QVBoxLayout{ midW };
	current = new QListWidget{};

	QVBoxLayout* vLayoutUpperPart = new QVBoxLayout{ uPart };
	vLayoutUpperPart->addWidget(new QLabel{ "Current dog" });
	vLayoutUpperPart->addWidget(midW);
	vLayoutUpperPart->addWidget(moveOneButton);
	vLayoutUpperPart->addWidget(moveAllButton);

	vLayoutMiddle->addWidget(uPart);
	vLayoutMiddle->addWidget(lPart);
	//vLayoutMiddle->addWidget(midW);
	

	QWidget* middleW = new QWidget{};
	QVBoxLayout* middleSide = new QVBoxLayout{ middleW };
	current = new QListWidget{};
	//this->current->setFixedHeight(200);

	//buttons
	QWidget* iteratorButtonsWidget = new QWidget{};
	QGridLayout* iteratorButtonsLayout = new QGridLayout{ iteratorButtonsWidget };
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

	rightSide->addWidget(new QLabel{ "Adoption list" });
	rightSide->addWidget(adoptionView);
	rightSide->addWidget(adoptionButtonsWidget);

	layout->addWidget(leftW);
	layout->addWidget(middleW);
	layout->addWidget(rightW);
	*/
}

void SecondWindow::populate()
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

void SecondWindow::add(Dog& d)
{
	try {
		model->addDogToRepository(d);
	}
	catch (RepoException& v)
	{
		std::cout << v.what();
		QMessageBox msgBox;
		msgBox.critical(0, "Error", "Dog already added to the adoption list!");

	}
}