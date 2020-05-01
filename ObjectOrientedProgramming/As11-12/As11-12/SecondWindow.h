#pragma once
#include <QtWidgets/qtableview.h>
#include <QtWidgets/QMainWindow>
#include "ui_As1112.h"
#include "DogModel.h"
#include <QSortFilterProxyModel>
#include "Controller.h"
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlistwidget.h>

#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qradiobutton.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qbuttongroup.h>

class SecondWindow : public QWidget
{
	Q_OBJECT

public:
	
	SecondWindow(Controller* c, QWidget *parent = 0);
	void add(Dog& d);



private:
	QTableView* adoptionView;
	QTableView* repoView;
	QListWidget* DogsListWidget;
	QListWidget* adoption;
	QListWidget* current;

	//form
	QLineEdit* nameInput;
	QLineEdit* breedInput;
	QLineEdit* ageInput;
	QLineEdit* sourceInput;
	QLineEdit* filterText;
	QLineEdit* newSourceInput;
	QLineEdit* newNameInput;
	QLineEdit* ageFilterInput;
	QLineEdit* breedFilterInput;


	//buttons
	QPushButton* addButton;
	QPushButton* deleteButton;
	QPushButton* UpdateButton;
	QPushButton* moveOneButton;
	QPushButton* moveAllButton;
	QPushButton* nextButton;
	QPushButton* openButton;
	QPushButton* adoptButton;
	QPushButton* openAdoptionButton;
	QPushButton* filterButton;
	QPushButton* undoButton;
	QPushButton* redoButton;
	QPushButton* newWindowButton;
	std::vector<std::unique_ptr<Action>> undoActions;
	std::vector<std::unique_ptr<Action>> redoActions;


	DogModel* model;
	Controller* ctrl;
	std::vector<Dog> dogs;
	std::vector<Dog> iteratedDogs;
	void init();
	void populate();
private:
	//Ui::As1112Class ui;
};
