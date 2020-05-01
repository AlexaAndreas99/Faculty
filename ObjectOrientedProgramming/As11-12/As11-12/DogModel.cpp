#include "DogModel.h"
#include "Repo.h"

DogModel::DogModel():QAbstractTableModel(),undoActions(),redoActions()
{
}

DogModel::DogModel(FileRepo * r)
{
	this->repo = r;
}


DogModel::~DogModel()
{
	delete repo;
}

int DogModel::rowCount(const QModelIndex & parent) const
{
	return repo->get_all()->size();
}

int DogModel::columnCount(const QModelIndex &) const
{
	return 4;
}

QVariant DogModel::data(const QModelIndex & index, int role) const
{
	if (!index.isValid() || role != Qt::DisplayRole)
		return QVariant();
	auto v = repo->get_all();
	auto tut = (*v)[index.row()];
	switch (index.column())
	{
	case 0: {return tr(tut.get_name().c_str()); }
	case 1: {return tr(tut.get_breed().c_str()); }
	case 2: {return tr(std::to_string(tut.get_age()).c_str()); }
	case 3: {return tr(tut.get_photo().c_str()); }
	default: {return QVariant(); }
	}
	return QVariant();
}

QVariant DogModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	{
		if (role != Qt::DisplayRole)
			return QVariant();

		if (orientation == Qt::Horizontal) {
			switch (section) {
			case 0:
				return tr("Name");

			case 1:
				return tr("Breed");
			case 2:
				return tr("Age");
			case 3:
				return tr("Source");
			default:
				return QVariant();
			}
		}
		return QVariant();
	}
}

void DogModel::undo()
{
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

	}
	catch (RepoException& e)
	{
		//cout << e.what() << endl;
	}
}

void DogModel::redo()
{
}

bool DogModel::addDogToRepository(Dog d)
{
	try {

		beginInsertRows(QModelIndex(), 0, 0);
		repo->add_dog(d);
		std::unique_ptr<Action> action{ new AddAction{ repo,d } };
		undoActions.push_back(std::move(action));
		redoActions.clear();
		endInsertRows();
		return true;
	}
	catch (RepoException &e)
	{
		throw e;
	}
	
	
}

bool DogModel::removeDogFromRepository(int row)
{
	Dog v = (*repo->get_all())[row];
	beginInsertRows(QModelIndex(), 0, 0);
	repo->remove_dog(v.get_name(), v.get_breed());
	std::unique_ptr<Action> action{ new RemoveAction{ repo,v } };
	undoActions.push_back(std::move(action));
	redoActions.clear();
	endInsertRows();
	return true;

}

Qt::ItemFlags DogModel::flags(const QModelIndex & index) const
{
	if (index.column() == 4)
		return Qt::DisplayRole;
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool DogModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	return true;
	/*
	if (!index.isValid() || role != Qt::EditRole)
		return false;

	int row = index.row();

	Dog p = (*repo->get_all())[row];
	try {

		switch (index.column()) {
		case 0: {
			/*
			std::string presenter = index.data().toString().toStdString();
			//repo->updateTutorial(Tutorial{ p.getTitle(),value.toString().toStdString(),Duration{ p.getDuration().getMinutes(),p.getDuration().getSeconds() },p.getNoLikes(),p.getSource(),p.getNoViews() }, presenter, p.getTitle());
			repo->updateTutorial(TutorialFactory::MakeTutorial(p.getTitle(), value.toString().toStdString(), std::to_string(p.getDuration().getMinutes()), std::to_string(p.getDuration().getSeconds()), std::to_string(p.getNoLikes()), p.getSource(), std::to_string(p.getNoViews())), presenter, p.getTitle());
			Tutorial newT = Tutorial{ p.getTitle(),value.toString().toStdString(),Duration{ p.getDuration().getMinutes(),p.getDuration().getSeconds() },p.getNoLikes(),p.getSource(),p.getNoViews() };
			std::unique_ptr<Action> action{ new UpdateAction(repo,p,newT) };
			undoActions.push_back(std::move(action));
			redoActions.clear();
			
		}
				break;
		case 1: {
			/*
			std::string title = index.data().toString().toStdString();
			repo->updateTutorial(TutorialFactory::MakeTutorial(value.toString().toStdString(), p.getPresenter(), std::to_string(p.getDuration().getMinutes()), std::to_string(p.getDuration().getSeconds()), std::to_string(p.getNoLikes()), p.getSource(), std::to_string(p.getNoViews())), p.getPresenter(), title);
			Tutorial newT = TutorialFactory::MakeTutorial(value.toString().toStdString(), p.getPresenter(), std::to_string(p.getDuration().getMinutes()), std::to_string(p.getDuration().getSeconds()), std::to_string(p.getNoLikes()), p.getSource(), std::to_string(p.getNoViews()));
			std::unique_ptr<Action> action{ new UpdateAction(repo,p,newT) };
			undoActions.push_back(std::move(action));
			redoActions.clear();
		};

				break;
				
		case 2: {
			std::string noLikes = value.toString().toStdString();
			repo->updateTutorial(TutorialFactory::MakeTutorial(p.getTitle(), p.getPresenter(), std::to_string(p.getDuration().getMinutes()), std::to_string(p.getDuration().getSeconds()), noLikes, p.getSource(), std::to_string(p.getNoViews())), p.getPresenter(), p.getTitle());
			Tutorial newT = TutorialFactory::MakeTutorial(p.getTitle(), p.getPresenter(), std::to_string(p.getDuration().getMinutes()), std::to_string(p.getDuration().getSeconds()), noLikes, p.getSource(), std::to_string(p.getNoViews()));
			std::unique_ptr<Action> action{ new UpdateAction(repo,p,newT) };
			undoActions.push_back(std::move(action));
			redoActions.clear();
		};
				break;
		case 3: {
			std::string noViews = value.toString().toStdString();
			repo->updateTutorial(TutorialFactory::MakeTutorial(p.getTitle(), p.getPresenter(), std::to_string(p.getDuration().getMinutes()), std::to_string(p.getDuration().getSeconds()), std::to_string(p.getNoLikes()), p.getSource(), value.toString().toStdString()), p.getPresenter(), p.getTitle());
			Tutorial newT = TutorialFactory::MakeTutorial(p.getTitle(), p.getPresenter(), std::to_string(p.getDuration().getMinutes()), std::to_string(p.getDuration().getSeconds()), std::to_string(p.getNoLikes()), p.getSource(), value.toString().toStdString());
			std::unique_ptr<Action> action{ new UpdateAction(repo,p,newT) };
			undoActions.push_back(std::move(action));
			redoActions.clear();
		}
				break;
		case 4: {
			std::string source = value.toString().toStdString();
			repo->updateTutorial(TutorialFactory::MakeTutorial(p.getTitle(), p.getPresenter(), std::to_string(p.getDuration().getMinutes()), std::to_string(p.getDuration().getSeconds()), std::to_string(p.getNoLikes()), source, std::to_string(p.getNoViews())), p.getPresenter(), p.getTitle());
			Tutorial newT = TutorialFactory::MakeTutorial(p.getTitle(), p.getPresenter(), std::to_string(p.getDuration().getMinutes()), std::to_string(p.getDuration().getSeconds()), std::to_string(p.getNoLikes()), source, std::to_string(p.getNoViews()));
			std::unique_ptr<Action> action{ new UpdateAction(repo,p,newT) };
			undoActions.push_back(std::move(action));
			redoActions.clear();
		}
				break;
		case 5: {
			std::string duration = value.toString().toStdString();
			std::vector<std::string> durationTokens = tokenize(duration, ':');
			if (durationTokens.size() != 2)
			{
				QMessageBox messageBox;
				messageBox.critical(0, "Error", "The duration must be formated as \"M:S\"!");
				return true;
			}
			repo->updateTutorial(TutorialFactory::MakeTutorial(p.getTitle(), p.getPresenter(), durationTokens[0], durationTokens[1], std::to_string(p.getNoLikes()), p.getSource(), std::to_string(p.getNoViews())), p.getPresenter(), p.getTitle());
			Tutorial newT = TutorialFactory::MakeTutorial(p.getTitle(), p.getPresenter(), durationTokens[0], durationTokens[1], std::to_string(p.getNoLikes()), p.getSource(), std::to_string(p.getNoViews()));
			std::unique_ptr<Action> action{ new UpdateAction(repo,p,newT) };
			undoActions.push_back(std::move(action));
			redoActions.clear();
		}
				break;
		};

	}
	catch (ValidationException& e)
	{

		QMessageBox messageBox;
		repo->updateTutorial(p, p.getPresenter(), p.getTitle());
		messageBox.critical(0, "Error", QString::fromStdString("Invalid data!"));
	}
	catch (RepositoryException& e)
	{
		std::cout << e.what();
		QMessageBox messageBox;
		repo->updateTutorial(p, p.getPresenter(), p.getTitle());

		messageBox.critical(0, "Error", "Cannot add element! Tutorial already existing");
	}

	emit dataChanged(index, index);

	return true;
	*/
}
