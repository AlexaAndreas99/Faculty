#include "Set.h"
#include <iostream>
#include <vector>

void Set::resize()///theta(m)
{
	std::vector<TKey> v;
	SetIterator it = this->iterator();
	it.first();
	while (it.valid()) {
		TKey e = it.getCurrent();
		v.push_back(e);
		it.next();
	}
	int oldcap = this->cap;
	this->cap *= 2;
	for (int i = 0; i < oldcap; i++)
		delete this->T[i];
	delete[] T;
	this->T = new Node*[this->cap];
	for (int i = 0; i < this->cap; i++)
		this->T[i] = nullptr;
	this->s = 0;
	for (auto i : v)
		this->add(i);
}

Set::Set(Tfunction t)///theta(m)
{
	this->T= new Node*[this->cap];
	this->h = t;
	for (int i = 0; i < this->cap; i++)
		this->T[i] = nullptr;
}

bool Set::add(TKey e)///o(m) amortised
{
	double r = this->s / this->cap;
	if (r > 0.7)
		this->resize();///theta(m)

	if(this->search(e))///o(m)
		return false;
	this->s++;
	int pos = this->h(e, this->cap);
	Node* newnode = new  Node;
	newnode->k = e;
	newnode->next = nullptr;
	Node* current = this->T[pos];
	newnode->next = current;
	this->T[pos] = newnode;
	return true;
}

bool Set::remove(TKey e)///o(m)
{
	if (!this->search(e))///o(m)
		return false;

	this->s--;

	int pos = this->h(e, this->cap);
	Node* current = this->T[pos];
	Node* prev = nullptr;
	while (current != nullptr&&current->k != e)
	{
		prev = current;
		current = current->next;
	}

	if (current != nullptr&&prev == nullptr)
	{
		this->T[pos] = this->T[pos]->next;
	}
	else
	{
		prev->next = current->next;
	}


	return true;
}

bool Set::search(TKey elem) const///o(m)
{
	int pos = this->h(elem, this->cap);

	Node* current = this->T[pos];
	while (current!=nullptr&&current->k!=elem)
	{
		current = current->next;
	}
	if (current!=nullptr)
		return true;

	return false;
}

int Set::size() const ///theta(1)
{
	/*
	int sum = 0;
	for (int i = 0; i < 10; i++)
	{
		Node* current = this->T[i];
		while (current != nullptr)
		{
			sum++;
			//std::cout << i << " " << current->k << std::endl;
			current = current->next;
		}
	}
	return sum;
	*/
	return this->s;
}

bool Set::isEmpty() const ///theta(1)
{
	return s==0;
}

SetIterator Set::iterator() const ///theta(1)
{
	return SetIterator(*this);
}

int Set::difference(const Set & s)
{
	int sum = 0;
	int ok;
	SetIterator it = this->iterator();
	it.first();
	while (it.valid()) {
		TKey e = it.getCurrent();
		
		ok = 0;
		int pos = s.h(e, s.cap);

		Node* current = s.T[pos];
		while (current != nullptr&&current->k != e)
		{
			current = current->next;
		}
		if (current != nullptr&&current->k==e)
			ok = 1;
		
		if (ok)
		{
			sum++;
			this->s--;

			int pos = this->h(e, this->cap);
			Node* current = this->T[pos];
			Node* prev = nullptr;
			while (current != nullptr&&current->k != e)
			{
				prev = current;
				current = current->next;
			}

			if (current != nullptr&&prev == nullptr)
			{
				this->T[pos] = this->T[pos]->next;
			}
			else
			{
				prev->next = current->next;
			}
		}

		it.next();
	}



	return sum;
}


Set::~Set()///theta(m)
{
	for (int i = 0; i < this->cap; i++)
		delete this->T[i];
	delete[] T;
}
