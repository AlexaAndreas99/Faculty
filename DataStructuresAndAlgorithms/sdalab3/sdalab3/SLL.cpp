#include "SLL.h"
#include <Windows.h>
#include <stdexcept>


SLL::SLL()
{
	this->head = new SLLnode;
}

struct SLLnode * SLL::search(Tvalue e)
{
	struct SLLnode *current = this->head;
	while (current != nullptr&&current->data != e)
	{
		current = current->next;
	}
	return current;
}

void SLL::insert_first(Tvalue e)
{
	struct SLLnode *newn = new SLLnode;
	newn->data = e;
	newn->next = this->head;
	this->head = newn;
}

void SLL::insert_after(SLLnode * currentn, Tvalue e)
{
	struct SLLnode *newn = new SLLnode;
	newn->data = e;
	newn->next = currentn->next;
	currentn->next = newn;
}

void SLL::insert_pos(int pos, Tvalue e)
{
	if (pos < 0)
	{
		throw std::exception("invalid pos!");
	}
	else if (pos == 0)
	{
		insert_first(e);
	}
	else
	{
		struct SLLnode *currentn = this->head;
		int current_pos = 0;
		while (current_pos < pos - 1 && currentn != nullptr)
		{
			currentn = currentn->next;
			current_pos++;
		}
		if (currentn != nullptr)
		{
			insert_after(currentn, e);
		}
		else
		{
			throw std::exception("invalid pos!");
		}
	}
}

SLLnode * SLL::delete_elem(Tvalue e)
{
	struct SLLnode *currentn = this->head;
	struct SLLnode *prevn = nullptr;
	while (currentn != nullptr&&currentn->data != e)
	{
		prevn = currentn;
		currentn = currentn->next;
	}
	if (currentn != nullptr&&prevn == nullptr)
	{
		this->head = this->head->next;
	}
	else if (currentn != nullptr)
	{
		prevn->next = currentn->next;
		currentn->next = nullptr;
	}
	return currentn;
}

SLLIterator SLL::iterator() const
{
	return SLLIterator(*this);
}


SLL::~SLL()
{
}
