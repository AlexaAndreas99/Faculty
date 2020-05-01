#include "SetIterator.h"
#include <exception>


SetIterator::SetIterator(const Set & c): c(c) ///o(m)
{
	this->currentPos = 0;
	while (this->currentPos < this->c.cap&&this->c.T[this->currentPos] == nullptr)
		this->currentPos++;
	if (this->currentPos < this->c.cap)
		this->currentNode = this->c.T[this->currentPos];
	else
		this->currentNode = nullptr;

}

void SetIterator::first()///o(m)
{
	this->currentPos = 0;
	while (this->currentPos < this->c.cap&&this->c.T[this->currentPos] == nullptr)
		this->currentPos++;
	if (this->currentPos < this->c.cap)
		this->currentNode = this->c.T[this->currentPos];
	else
		this->currentNode = nullptr;

}

void SetIterator::next()///BC: theta(1) AC: o(m)
{
	if (this->valid() == false)
	{
		throw std::exception("null pointer!");
	}
	if (this->currentNode->next != nullptr)
		this->currentNode = this->currentNode->next;
	else
	{
		this->currentPos++;
		while (this->currentPos < this->c.cap&&this->c.T[this->currentPos] == nullptr)
		{
			this->currentPos++;
		}
		if (this->currentPos < this->c.cap)
			this->currentNode = this->c.T[this->currentPos];
		else
			this->currentNode = nullptr;

	}
}

bool SetIterator::valid() const ///thete(1)
{
	return this->currentNode!=nullptr;
}

TKey SetIterator::getCurrent() const ///theta(1)
{
	if (this->valid() == false)
	{
		throw std::exception("null pointer!");
	}
	return this->currentNode->k;
}

SetIterator::~SetIterator()
{
}
