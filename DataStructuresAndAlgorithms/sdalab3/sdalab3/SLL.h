#pragma once
#include <utility>
#include <vector>
#include "SLLIterator.h"

typedef int Tkey;
typedef int Tvalue;
typedef std::pair<Tkey, Tvalue> Telem;

//class SLLIterator

class SLL
{
	friend class SMMIterator;
	friend class SLLIterator;
	friend class SortedMultiMap;
private:
	struct SLLnode *head;
public:
	SLL();
	//o(n)
	struct SLLnode* search(Tvalue e);
	//theta(1)
	void insert_first(Tvalue e);
	//theta(1)
	void insert_after(struct SLLnode *currentn, Tvalue e);
	//o(n)
	void insert_pos(int pos, Tvalue e);
	//o(n)
	struct SLLnode* delete_elem(Tvalue e);
	//theta(1)
	SLLIterator iterator() const;
	~SLL();
};

typedef std::pair<Tkey, SLL> TSll;
struct SLLother
{
	TSll data;
	struct SLLother* next;
};