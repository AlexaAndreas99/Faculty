#pragma once
#include "SortedBag.h"

typedef int Tcomp;
typedef Tcomp Telem;
typedef bool(*Relation)(Tcomp, Tcomp);
class BagIterator
{
private:
	friend class SortedBag;
	//theta(1)
	BagIterator( const SortedBag& sb);
    const SortedBag& sb;
	
public:
	int index;
	//theta(1)
	void first();
	//theta(1)
	void next();
	//theta(1)
	bool valid()const;
	//theta(1)
	Tcomp getCurrent() const;
};

