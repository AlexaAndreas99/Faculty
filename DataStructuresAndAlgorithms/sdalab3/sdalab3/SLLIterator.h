#pragma once
#include "SLL.h"
#include <utility>

typedef int Tkey;
typedef int Tvalue;
typedef std::pair<Tkey, Tvalue>Telem;
struct SLLnode
{
	Tvalue data;
	struct SLLnode* next;
};
class SLL;
class SortedMultiMap;
class SMMIterator;

class SLLIterator
{
	friend class SLL;
	friend class SortedMultiMap;
	friend class SMMIterator;
private:
	const SLL& sll;
	SLLnode* currentn;
	//theta(1)
	SLLIterator(const SLL& othersll);
public:
	//theta(1)
	void first();
	//theta(1)
	bool valid();
	//theta(1)
	void next();
	//theta(1)
	SLLnode *getCurrent();
	~SLLIterator();
};

