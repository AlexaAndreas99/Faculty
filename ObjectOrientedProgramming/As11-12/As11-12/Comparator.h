#pragma once
#include "Dog.h"
typedef Dog Telem;

template <typename T>
class Comparator
{
public:
	//template <typename T>
	virtual bool compare(T e1, T e2) const = 0;
};

class comparator_by_age : public Comparator<Telem>
{
public:
	comparator_by_age();
	bool compare(Telem e1, Telem e2) const override;
	~comparator_by_age();
};

class comparator_by_breed : public Comparator<Telem>
{
public:
	comparator_by_breed();
	bool compare(Telem e1, Telem e2) const override;
	~comparator_by_breed();
};