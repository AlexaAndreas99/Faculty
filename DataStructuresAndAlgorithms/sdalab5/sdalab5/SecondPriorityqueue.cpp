#include <iostream>
#include <iomanip>
#include "SecondPriorityqueue.h"

SecondPriorityQueue::SecondPriorityQueue(Relation r)//theta(1)
{
	this->size = 0;
	this->cap = 10;
	this->r = r;
	this->elems = new Element[this->cap];
}

void SecondPriorityQueue::push(TElem e, TPriority p)//o(n) amortised
{
	if (this->size == this->cap)
		this->resize();//theta(n)
	this->elems[this->size]= std::make_pair(e, p);
	this->size++;
	this->bubble_up(this->size-1);//o(log(n))
	
}

Element SecondPriorityQueue::top() const//theta(1)
{

	if (this->atMostOne())//theta(1)
		throw std::exception("The queue has less than 2 elements");

	auto max = this->elems[1];
	if (this->size > 2 && this->r(this->elems[2].second, max.second))
		max = this->elems[2];
	if (this->size > 3 && this->r(this->elems[3].second, max.second))
		max = this->elems[3];
	//std::cout << max.first;
	return max;
}

Element SecondPriorityQueue::pop()//o(log(n))
{

	if (this->atMostOne())//theta(1)
		throw std::exception("The queue has less than 2 elements");

	/*
	auto e = this->elems[1];
	for (int i = 1; i < this->size - 1; i++)
		this->elems[i] = this->elems[i + 1];
	this->size--;
	return e;
	*/
	auto max = this->elems[1];
	int i = 1;
	if (this->size > 2 && this->r(this->elems[2].second, max.second))
	{
		max = this->elems[2];
		i = 2;
	}
	if (this->size > 3 && this->r(this->elems[3].second, max.second))
	{
		max = this->elems[3];
		i = 3;
	}


	auto deleted = max;
	//std::cout << deleted.first<<" "<<i;
	this->elems[i] = this->elems[this->size - 1];
	this->size--;
	this->bubble_down(i);//o(log(n))
	return deleted;
}

bool SecondPriorityQueue::atMostOne() const//theta(1)
{
	return this->size<=1;
}

SecondPriorityQueue::~SecondPriorityQueue()//theta(1)
{
	delete[] this->elems;
}

void SecondPriorityQueue::print()
{
	std::cout << "Elems: ";
	for (int i = 0; i < this->size; ++i) {
		std::cout << left << setw(3) << this->elems[i].first << ' ';
	}
	std::cout << "\nPrior: ";
	for (int i = 0; i < this->size; ++i) {
		std::cout << left << setw(3) << this->elems[i].second << ' ';
	}
	std::cout << "\n";
}

void SecondPriorityQueue::bubble_up(int p)//o(log(n))
{
	int poz = p;
	auto elem = this->elems[p];
	int parent = (p-1) / 3;
	while (poz > 0 && !this->r(this->elems[parent].second,elem.second))
	{
		this->elems[poz] = this->elems[parent];
		poz = parent;
		parent = (poz-1) / 3;
	}
	this->elems[poz] = elem;
}

void SecondPriorityQueue::bubble_down(int p)//o(log(n))
{
	int poz = p;
	auto elem = this->elems[p];
	while (poz < this->size-1)
	{
		auto maxChild = -1;
		if (poz * 3+1 <= this->size)//left
			maxChild = poz * 3+1;

		if (poz * 3 + 2 <= this->size && this->r(this->elems[3 * poz + 2].second, this->elems[maxChild].second))//mid
			maxChild = poz * 3 + 2;
		
		if (poz * 3 + 3 <= this->size && this->r(this->elems[3 * poz + 3].second, this->elems[maxChild].second))
			maxChild = poz * 3 + 3;



		if (maxChild != -1 && this->r(this->elems[maxChild].second, elem.second))
		{
			auto tmp = this->elems[poz];
			this->elems[poz] = this->elems[maxChild];
			this->elems[maxChild] = tmp;
			poz = maxChild;
		}
		else
			poz = this->size + 1;
	}
}

void SecondPriorityQueue::resize()//theta(n)
{
	this->cap *= 2;
	Element* newElems = new Element[this->cap];

	for (int i = 0; i < this->size; ++i)
		newElems[i] = this->elems[i];
	
	delete[] this->elems;
	this->elems = newElems;
}


