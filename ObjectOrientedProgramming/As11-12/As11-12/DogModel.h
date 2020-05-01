#pragma once
#include <QObject>
#include <QAbstractTableModel>
#include "FileRepo.h"
#include <functional>
#include <vector>
#include "Undo.h"
#include <memory>
class DogModel: public QAbstractTableModel
{
private:
	FileRepo* repo;
public:
	std::vector<std::unique_ptr<Action>> undoActions;
	std::vector<std::unique_ptr<Action>> redoActions;
	DogModel();
	DogModel(FileRepo* r);
	~DogModel();

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &/*parent*/) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	void undo();
	void redo();


	// repository
	FileRepo* getRepo() { return repo; };
	bool addDogToRepository(Dog t);
	bool removeDogFromRepository(int row);
	Qt::ItemFlags flags(const QModelIndex & index) const override;
	bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) override;

};

