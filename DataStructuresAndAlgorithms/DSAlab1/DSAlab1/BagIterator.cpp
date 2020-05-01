#include "BagIterator.h"
#include <stdexcept>

BagIterator::BagIterator(const SortedBag & sb): sb(sb)
{
	this->index = 0;

}

void BagIterator::first()
{
	this->index = 0;
}

void BagIterator::next()
{
	if (valid() == 0)
	{
		throw std::invalid_argument("Invalid iterator!");
	}
	this->index++;

}

bool BagIterator::valid() const
{
	return this->index < sb.size();
}

Tcomp BagIterator::getCurrent() const
{
	if (valid() == 0)
	{
		throw std::invalid_argument("Invalid iterator!");
	}

	return sb.bag.getElement(this->index);
}
