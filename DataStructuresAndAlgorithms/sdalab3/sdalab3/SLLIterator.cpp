#include "SLLIterator.h"


SLLIterator::SLLIterator(const SLL & othersll):sll(othersll)
{
	this->currentn = othersll.head;
}

void SLLIterator::first()
{
	this->currentn = this->sll.head;
}

bool SLLIterator::valid()
{
	return this->currentn != nullptr;
}

void SLLIterator::next()
{
	if (this->valid() == false)
	{
		throw std::exception("null pointer!");
	}
	this->currentn = this->currentn->next;
}

SLLnode * SLLIterator::getCurrent()
{
	if (this->valid() == false)
	{
		throw std::exception("null pointer!");
	}
	return this->currentn;
}

SLLIterator::~SLLIterator()
{
}
