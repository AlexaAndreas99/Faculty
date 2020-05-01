#pragma once
#include "Set.h"
typedef int TKey;
typedef struct Node;
class Set;
class SetIterator{
	friend class Set;
private:
	SetIterator(const Set& c);
	const Set& c;
	int currentPos;
	Node* currentNode;
public:
	void first();
	void next();
	bool valid() const;
	TKey getCurrent() const;
	~SetIterator();


};


