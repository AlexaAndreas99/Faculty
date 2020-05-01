#pragma once
#include "DynamicVector.h"
#include "BagIterator.h"
typedef int Tcomp;
typedef Tcomp Telem;
typedef bool(*Relation)(Tcomp, Tcomp);


class SortedBag
{
private:
	DynamicVector<Tcomp> bag;
	Relation r;
	friend class BagIterator;
public:
	//theta(1)
	SortedBag(Relation r);
	~SortedBag();

	//o(n)
	void add(Tcomp e);
	//o(n)
	bool remove(Tcomp e);
	//o(n)
	bool search(Tcomp e) ;
	//o(n)
	int pos(Tcomp e);
	//theta(1)
	int size()const {return this->bag.get_size();}
	//o(n)
	int nrOccurrences(Tcomp e);
	//theta(1)
	bool isEmpty() {return this->bag.get_size() == 0;}
	//theta(1)
	BagIterator iterator() const;

	int elementsWithMinimumFrequency() const;
};

