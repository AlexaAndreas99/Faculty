#pragma once
#include "FileRepo.h"

class Action {
public:
	Action() {};
	virtual void undo() = 0;
	virtual void redo() = 0;
};

class AddAction: public Action {
public:
	AddAction(FileRepo* f, Dog d) :Action(), repo(f), dog(d) {};
	FileRepo* repo;
	Dog dog;
	void undo() override {
		repo->remove_dog(dog.get_name(), dog.get_breed());
	};
	void redo() override {
		repo->add_dog(dog);
	};
};

class RemoveAction :public Action {
public:
	RemoveAction(FileRepo* f, Dog d) :Action(), repo(f), dog(d) {};
	FileRepo* repo;
	Dog dog;
	void undo() override {
		repo->add_dog(dog);};
	void redo() override {
		repo->remove_dog(dog.get_name(), dog.get_breed());

	};
};

class UpdateAction :public Action {
public:
	UpdateAction(FileRepo* f, Dog old,Dog newd) :Action(), repo(f), odog(old),ndog(newd) {};
	FileRepo* repo;
	Dog odog;
	Dog ndog;
	void undo() override {
		repo->update(odog, ndog);
	};
	void redo() override {
		repo->update(ndog, odog);

	};
};
