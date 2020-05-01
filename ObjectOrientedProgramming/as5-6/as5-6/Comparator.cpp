#include "Comparator.h"
#include "Dog.h"
//typedef Dog Telem;
comparator_by_age::comparator_by_age()
{

}

bool comparator_by_age::compare(Telem e1, Telem e2) const
{
	return e1.get_age() <= e2.get_age();
}

comparator_by_age::~comparator_by_age()
{
}

bool comparator_by_breed::compare(Telem e1, Telem e2) const
{
	return e1.get_breed()<=e2.get_breed();
}
