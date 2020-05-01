#include "SMMIterator.h"

SMMIterator::SMMIterator(const Container& c) : c{ c } {
	this->currentIndex = this->c.head;
	this->current = this->c.nodes[this->c.head].head;
}

SMMIterator::~SMMIterator()
{
}

void SMMIterator::first()
{
	this->currentIndex = this->c.head;
	this->current = this->c.nodes[c.head].head;
}

void SMMIterator::next()
{
	if (this->valid())
	{
		this->current = this->c.nodes[this->currentIndex].slla[this->current].next;
		if (this->current == -1)
		{
			this->currentIndex = this->c.nodes[this->currentIndex].next;
			if (this->currentIndex != -1) {
				this->current = this->c.nodes[this->currentIndex].head;
			}
		}
	}
	else
		throw exception();
}

bool SMMIterator::valid() const
{
	if (this->currentIndex == -1)
		return false;
	return true;
}

Telem SMMIterator::getCurrent() const
{
	Telem thing(this->c.nodes[this->currentIndex].key, this->c.nodes[this->currentIndex].slla[this->current].info);
	return thing;
}
