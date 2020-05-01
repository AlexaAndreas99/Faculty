#pragma once
#include <utility>
#include <vector>
#include "SLL.h"
#include "SMMIterator.h"
#include "SLLIterator.h"

typedef int Tkey;
typedef int Tvalue;
typedef std::pair<Tkey, Tvalue> Telem;
typedef std::pair<Tkey, SLL>TSll;
typedef bool(*Relation)(Tkey, Tkey);

class SMMIterator;
class SLL;
class SLLIterator;


class SortedMultiMap
{
	friend class SMMIterator;
private:
	SLLother* head;
	Relation r;
public:
	//theta(1)
	SortedMultiMap(Relation r);
	//o(n)
	void add(Tkey c, Tvalue v);
	//o(n)
	std::vector<Tvalue> search(Tkey c) const;
	//o(n)
	std::pair < SLLother*, SLLother*> internal_search(Tkey c);
	//o(n)
	bool remove(Tkey c, Tvalue v);
	
	int size() const;
	//theta(1)
	bool isEmpty()const;
	//theta(1)
	SMMIterator iterator()const;
	void replace(Tkey k, Tvalue old_value, Tvalue new_value);
	~SortedMultiMap();
};

