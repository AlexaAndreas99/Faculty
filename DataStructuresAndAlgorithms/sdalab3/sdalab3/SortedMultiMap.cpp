#include "SortedMultiMap.h"



SortedMultiMap::SortedMultiMap(Relation r)
{
	this->head = nullptr;
	this->r = r;
}

void SortedMultiMap::add(Tkey c, Tvalue v)
{
	SLLother* currentn = new SLLother;
	SLLother* prevn = new SLLother;
	std::pair < SLLother*, SLLother*> node;
	node=this->internal_search(c);
	currentn = node.first;
	prevn = node.second;
	if (this->head == nullptr)
	{
		SLL vl;
		vl.insert_first(v);
		vl.head->next = nullptr;
		this->head = new SLLother;
		this->head->data.first = c;
		this->head->data.second = vl;
		this->head->next = nullptr;
	}
	else if (currentn!=nullptr&&currentn->data.first == c)
	{
		currentn->data.second.insert_first(v);
	}
	else
	{
		SLL node;
		SLLother* new_node = new SLLother;
		new_node->data.first = c;
		new_node->data.second = node;
		new_node->data.second.head->next = nullptr;
		node.insert_first(v);
		if (prevn == nullptr)
		{
			new_node->next = this->head;
			this->head = new_node;
			
		}
		else
		{
			new_node->next = currentn;
			prevn->next = new_node;

		}
	}
}

std::vector<Tvalue> SortedMultiMap::search(Tkey c) const
{
	std::vector<Tvalue> vl;
	SLLother* currentn = new SLLother;
	SLLother* prevn = new SLLother;
	SLLnode* node = new SLLnode;

	currentn = this->head;
	prevn = nullptr;
	while (currentn != nullptr&&currentn->data.first != c && this->r(currentn->data.first, c))
	{
		prevn = currentn;
		currentn = currentn->next;
	}
	if (currentn==nullptr || currentn->data.first !=c) 
		return vl;
	node = currentn->data.second.head;
	while (node != nullptr)
	{
		vl.push_back(node->data);
		node = node->next;

	}
	return vl;
}

std::pair < SLLother*, SLLother*> SortedMultiMap::internal_search(Tkey c)
{
	/*
	precondition: Tkey c a valid key
	postcondition: a pair<sllother*,sllother*> currentn=the address of the node c if exists or prev=the address of the node where c should be inserted
	*/
	SLLother* currentn = this->head;
	SLLother* prevn = nullptr;
	while (currentn != nullptr&& currentn->data.first != c && this->r(currentn->data.first, c))
	{
		prevn = currentn;
		currentn = currentn->next;
	}
	std::pair < SLLother*, SLLother*> node;
	node.first = currentn;
	node.second = prevn;
	return node;
}

bool SortedMultiMap::remove(Tkey c, Tvalue v)
{
	SLLother* currentn = new SLLother;
	SLLother* prevn = new SLLother;
	std::pair < SLLother*, SLLother*> node;
	node = this->internal_search(c);
	currentn = node.first;
	prevn = node.second;

	if(currentn==nullptr)
		return false;
	if (currentn->data.first == c)
	{
		auto rem = currentn->data.second.delete_elem(v);
		if (rem == nullptr)
		{
			if (currentn->data.second.head == nullptr)
			{
				while (this->head != currentn)
					this->head = this->head->next;
				this->head = currentn->next;
			}
			return false;
		}
		if (rem->data == v)
			return true;
	}
	return false;
}

int SortedMultiMap::size() const
{
	SLLother* currentn = this->head;
	SLLnode * inn = nullptr;
	int k = 0;
	if (this->isEmpty())
		return 0;
	while (currentn != nullptr)
	{
		inn = currentn->data.second.head;
			while (inn!= nullptr)
			{
				inn = inn->next;
				k++;
			}
		currentn = currentn->next;
	}
	return k;
}

bool SortedMultiMap::isEmpty() const
{
	return this->head == nullptr;
}


SMMIterator SortedMultiMap::iterator() const
{
	return SMMIterator(*this);
}

void SortedMultiMap::replace(Tkey k, Tvalue old_value, Tvalue new_value)
{
	SLLother* currentn = this->head;
	SLLother* prevn = nullptr;
	while (currentn != nullptr&& currentn->data.first != k && this->r(currentn->data.first, k))
	{
		prevn = currentn;
		currentn = currentn->next;
	}
	if (currentn == nullptr|| currentn->data.first != k)
		return ;
	auto rem = currentn->data.second.delete_elem(old_value);
	if (rem->data == old_value)
		currentn->data.second.insert_first(new_value);

}


SortedMultiMap::~SortedMultiMap()
{
}
