#pragma once
#include <vector>
#include <utility>
#include "BSTNode.h"

using namespace std;
typedef int Tkey;
typedef int Tvalue;
typedef std::pair<Tkey, Tvalue> Telem;
class SMMIterator;
typedef bool(*Relation)(Tkey, Tkey);


class SortedMultiMap
{
private:
	BSTNode *tree;
	int root;
	int numberOfElements;
	int capacity;
	int firstFree;
	Relation r;

	
	void changeFirstFree();
	bool mustBeResized();
	void resize();
	//Telem getMinimum(int startingRoot);
	//Telem getMaximum(int startingRoot);
	int removeRecursively(int node, Telem e, bool &removed);

public:
	friend class SMMIterator;
	//theta(n)
	SortedMultiMap(Relation r);
	//o(n)
	void add(Tkey c, Tvalue v);
	//o(n)
	vector<Tvalue> search(Tkey c)const;
	//o(n)
	bool remove(Tkey c, Tvalue v);
	void replace(Tkey k, Tvalue oldValue, Tvalue newValue);
	//theta(1)
	int size()const;
	//theta(1)
	bool isEmpty()const;
	//theta(1)
	//SMMIterator iterator() const;
	//remove a key togheter with all its values
	//returns a vector with the values of the keys
	vector<Tvalue> remove_key(Tkey k);
	~SortedMultiMap();
};

