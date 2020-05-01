#include "SMMIterator.h"



SMMIterator::SMMIterator(const SortedMultiMap& othersmm):smm(othersmm)
{
	this->currentn = othersmm.head;
}

void SMMIterator::first()
{
	this->currentn = this->smm.head;
}

bool SMMIterator::valid()
{
	return this->currentn != nullptr;
}

void SMMIterator::next()
{
	if (this->valid() == false)
	{
		throw std::exception("null pointer!");
	}
	this->currentn = this->currentn->next;
}

Telem SMMIterator::getCurrent()
{
	if (this->valid() == false)
	{
		throw std::exception("null pointer!");
	}
	return Telem(this->currentn->data.first, this->currentn->data.second.head->data);
}


SMMIterator::~SMMIterator()
{
}
