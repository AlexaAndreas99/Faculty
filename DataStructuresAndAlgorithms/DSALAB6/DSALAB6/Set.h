#pragma once
#include "SetIterator.h"
#include <math.h>



typedef int TKey;

typedef struct Node
{
	TKey k;
	Node* next;
}; 
typedef int(*Tfunction)(TKey t,int cap);



class SetIterator;
class Set {
	friend class SetIterator;
private:
	/* representation of Set*/
	Node** T;
	int s=0;
	int cap=10;
	Tfunction h;
	void resize();
public:
	
	//implicit constructor
	Set(Tfunction t);
	
	//adds an element to the  set
	//if the element was added, the operation returns true, otherwise (if the element was already in the set) 
	//it returns false
	bool add(TKey e);

	//removes an element from the set
	//if the element was removed, it returns true, otherwise false
	bool remove(TKey e);
	
	//checks if an element is in the  set
	bool search(TKey elem) const;
	
	//returns the number of elements;
	int size() const;
	
	//checks if the set is empty
	bool isEmpty() const;
	
	//returns an iterator for the set
	SetIterator iterator() const;
	
	int difference(const Set&s);
	//destructor
	~Set();
};