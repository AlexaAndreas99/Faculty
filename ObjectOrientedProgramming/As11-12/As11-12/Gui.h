#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qlistview.h>
#include <QtWidgets/qtableview.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qradiobutton.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qbuttongroup.h>
#include "Controller.h"
#include "Repo.h"
#include "Dog.h"
#include <vector>
#include "DogModel.h"
#include <QSortFilterProxyModel>
#include "SecondWindow.h"
#include <QEvent>
#include <QKeyEvent>


class Gui:public QWidget
{
	Q_OBJECT
public:
	Gui(Controller* c,QWidget* parent=0);
	~Gui();
protected:
	void keyPressEvent(QKeyEvent* event) Q_DECL_OVERRIDE;

private:
	//list
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

	SecondWindow* sec;

	DogModel* model;
	Controller* ctrl;
	std::vector<Dog> dogs;
	std::vector<Dog> iteratedDogs;
	int currentDog;
	void init();
	void populate();
	int getDogIndex();

private slots:
	void connectSignalAndSlots();
	void moveDogToAdoption();
	void deleteDog();
	void moveAllDogs();
	void addNewDog();
	void filterDogs();
	void updateDog();
	void next();
	void open();
	void openAdoption();
	void iteratedFilter();
	void undo();
	void redo();
	void new_window();
};

