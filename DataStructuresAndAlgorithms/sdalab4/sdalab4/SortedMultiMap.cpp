#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <iostream>

int SortedMultiMap::instance(Tkey searched) const
{//pos of the key
	int i = this->head;
	while (i != -1)
	{
		if (this->nodes[i].key == searched)
			return i;
		i = this->nodes[i].next;
	}
	return -1;
}

int SortedMultiMap::find_pos(Tkey searched)
{//pos of the element to be inserted
	int i = this->head;
	if (i == -1 || r(this->nodes[i].key, searched) == false)
		return -1;
	while (this->nodes[i].next != -1)
	{
		if (r(this->nodes[i].key, searched) && r(this->nodes[this->nodes[i].next].key, searched) == false)
			return i;
		if (this->nodes[i].next == -1)
			return i;
		i = this->nodes[i].next;
	}
	return i;
}

void SortedMultiMap::new_node(Tkey c, Tvalue v, int pos)
{
	this->nodes[pos].slla = new value_node[this->nodes[pos].cap];
	for (int i = 0; i < this->nodes[pos].cap; i++)
		this->nodes[pos].slla[i].next = i + 1;
	this->nodes[pos].first_empty = 0;
	this->nodes[pos].slla[this->nodes[pos].cap - 1].next = -1;
	this->nodes[pos].slla[this->nodes[pos].first_empty].info = v;
	this->nodes[pos].head = this->nodes[pos].first_empty;
	this->nodes[pos].first_empty = this->nodes[pos].slla[this->nodes[pos].first_empty].next;
	this->nodes[pos].slla[this->nodes[pos].head].next = -1;
	this->nodes[pos].key = c;
}

void SortedMultiMap::resize_key_node(int pos)
{
	this->nodes[pos].cap *= 2;
	value_node* aux = new value_node[this->nodes[pos].cap];
	int i = this->nodes[pos].head;
	while (i != -1)
	{
		aux[i].info = this->nodes[pos].slla[i].info;
		aux[i].next = this->nodes[pos].slla[i].next;
		i = this->nodes[pos].slla[i].next;
	}
	for (i = this->nodes[pos].cap / 2; i < this->nodes[pos].cap; i++)
	{
		aux[i].next = i + 1;
	}
	aux[this->nodes[pos].cap - 1].next = -1;
	delete[] this->nodes[pos].slla;
	this->nodes[pos].slla = aux;
	this->nodes[pos].first_empty = this->nodes[pos].cap / 2;
}

void SortedMultiMap::resize()
{
	this->capacity *= 2;
	key_node* aux = new key_node[this->capacity];
	int i = this->head;
	while (i != -1)
	{
		aux[i] = this->nodes[i];
		i = this->nodes[i].next;
	}
	for (i = this->size_smm; i < this->capacity; i++)
	{
		aux[i].next = i + 1;
		aux[i].slla = nullptr;
	}
	aux[this->capacity - 1].next = -1;
	delete[] this->nodes;
	this->nodes = aux;
	this->first_empty = this->size_smm;
}

SortedMultiMap::SortedMultiMap(Relation r):r{r}
{
	this->head = -1;
	this->first_empty = 0;
	this->nodes = new key_node[this->capacity];
	this->size_smm = 0;
	for (int i = 0; i < this->capacity; i++)
	{
		this->nodes[i].next = i + 1;
		this->nodes[i].slla = nullptr;

	}
	this->nodes[this->capacity - 1].next = -1;
}

void SortedMultiMap::add(Tkey c, Tvalue v)
{
	int pos = this->instance(c);
	if (pos != -1)
	{
		if (this->nodes[pos].first_empty == -1)
		{
			this->resize_key_node(pos);
		}
		this->nodes[pos].slla[this->nodes[pos].first_empty].info = v;
		int ver = this->nodes[pos].first_empty;
		this->nodes[pos].first_empty = this->nodes[pos].slla[this->nodes[pos].first_empty].next;
		this->nodes[pos].slla[ver].next = -1;
		int i = this->nodes[pos].head,j;
		while (i != -1)
		{
			j = i;
			i = this->nodes[pos].slla[i].next;
		}
		this->nodes[pos].slla[j].next = ver;
		this->key_values++;
	}
	else
	{
		if (this->first_empty == -1)
		{
			this->resize();
		}
		pos = this->find_pos(c);
		this->new_node(c, v, this->first_empty);
		if (pos != -1)
		{
				int temp = this->nodes[this->first_empty].next;
				this->nodes[this->first_empty].next = this->nodes[pos].next;
				this->nodes[pos].next = this->first_empty;
				this->first_empty = temp;
			
			this->size_smm++;
			this->key_values++;
		}
		else
		{
			if (this->head == -1)
			{
				this->head = this->first_empty;
				this->first_empty = this->nodes[this->first_empty].next;
				this->nodes[this->head].next = -1;
			}
			else
			{
				int temp = this->nodes[this->first_empty].next;
				this->nodes[this->first_empty].next = this->head;
				this->head = this->first_empty;
				this->first_empty = temp;
			}
			this->size_smm++;
			this->key_values++;
		}
	}
}

vector<Tvalue> SortedMultiMap::search(Tkey c) const
{
	int here = this->instance(c);
	vector<Tvalue> v;
	if (here == -1)
		return v;
	else
	{
		int i = this->nodes[here].head;
		while (i != -1)
		{
			v.push_back(this->nodes[here].slla[i].info);
			i = this->nodes[here].slla[i].next;
		}
	}
	return v;
}

bool SortedMultiMap::remove(Tkey c, Tvalue v)
{
	int here = this->instance(c);
	if (here != -1)
	{
		int i = this->nodes[here].head;
		while (i != -1)
		{

			if (this->nodes[here].slla[i].info == v)
			{
				if (this->nodes[here].head == i && this->size_smm == 1)
				{
					delete[] this->nodes[here].slla;
					this->nodes[here].slla = nullptr;
					this->key_values--;
					this->size_smm--;

					if (here == this->head) {
						//here is head
						this->head = this->nodes[head].next;
						this->nodes[here].next = this->first_empty;
						this->first_empty = here;
					}
				
				return true;
				}
				else
				{
					if (this->nodes[here].head == i)
					{//head
						this->nodes[here].head = this->nodes[here].slla[i].next;
						this->key_values--;
						this->nodes[here].slla[i].next = this->nodes[here].first_empty;
						this->nodes[here].first_empty = i;
						return true;
					}
					else
					{
					//random node
					this->nodes[here].first_empty = i;
					this->key_values--;
					this->nodes[here].slla[i].next = this->nodes[here].first_empty;
					this->nodes[here].first_empty = i;
					return true;


					}
				}
		
			}
			i = this->nodes[here].slla[i].next;
		}
	}
	return false;
}

void SortedMultiMap::replace(Tkey k, Tvalue oldValue, Tvalue newValue)
{
	int i = this->head;
	while (i != -1&&!this->nodes[i].key == k)
		i= this->nodes[i].next;
	if (i == -1)
		return;

	int j = this->nodes[i].head;

	while (j != -1)
	{
	if (this->nodes[i].slla[j].info == oldValue)
			this->nodes[i].slla[j].info = newValue;
	
	j = this->nodes[i].slla[j].next;
	}
}


int SortedMultiMap::size() const
{
	return this->key_values;
}

bool SortedMultiMap::isEmpty() const
{
	return this->size_smm==0;
}


SMMIterator SortedMultiMap::iterator() const
{
	return SMMIterator(*this);
}

vector<Tvalue> SortedMultiMap::remove_key(Tkey k)
{
	vector<Tvalue> v;
	
	int here = this->instance(k);
	int i = this->nodes[here].head;
	while (i != -1)
	{
		//std::cout << i;
		std::cout << this->nodes[here].slla[i].info;
		i = this->nodes[here].slla[i].next;
	}

	
	
	return v;
}

SortedMultiMap::~SortedMultiMap()
{
}
