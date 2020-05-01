#include "SortedBag.h"
#include <climits>



SortedBag::SortedBag(Relation r)
{
	this->r = r;
}

SortedBag::~SortedBag()
{
}

void SortedBag::add(Tcomp e)
{
	
	int pos = 0;
	while (pos < this->bag.get_size() && e != this->bag.getElement(pos) && !this->r(e,this->bag.getElement(pos)))
		pos++;
	this->bag.add_to_pos(pos,e);
}

bool SortedBag::remove(Tcomp e)
{
	if(search(e)==false)
		return false;
	
	int i = this->pos(e);
	this->bag.remove(i);
	
	return true;
}

bool SortedBag::search(Tcomp e)
{
	Tcomp* el = this->bag.getAll();
	for (int i = 0; i < this->bag.get_size(); i++)
		if (el[i] == e)
			return true;

	return false;
}

int SortedBag::pos(Tcomp e)
{
	Tcomp* el = this->bag.getAll();
	for (int i = 0; i < this->bag.get_size(); i++)
		if (el[i] == e)
			return i;

}

int SortedBag::nrOccurrences(Tcomp e)
{
	int s = 0;
	Tcomp* el = this->bag.getAll();
	for (int i = 0; i < this->bag.get_size(); i++)
		if (el[i] == e)
			s++;
	return s;
}

BagIterator SortedBag::iterator()const
{

	return BagIterator(*this);
}

int SortedBag::elementsWithMinimumFrequency() const
{
	if(this->size()==0)
		return 0;

	int min ,i,k=0,v[10000],c[10000],n=0,ok;
	auto it = this->iterator();
	it.first();
	while (it.valid())
	{

		ok = 0;
		for (i = 0; i < n; i++)
			if (it.getCurrent() == v[i])
			{
				c[i]++;
				ok = 1;
				if (c[i] < min)
					min = c[i];
			}
		if (ok == 0)
		{
			v[n] = it.getCurrent();
			c[n] = 1;
			n++;
			min = 1;
		}
		it.next();
	}
	for (i = 0; i < n; i++)
		if (min == c[i])
			k++;
	
	return k;
}
