#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <iostream>

void SortedMultiMap::changeFirstFree()
{
	++firstFree;
	while (firstFree < capacity && !tree[firstFree].isNull())
		++firstFree;

}

bool SortedMultiMap::mustBeResized()
{
	return firstFree >= capacity;
}

void SortedMultiMap::resize()
{
	BSTNode *newTree = new BSTNode[capacity * 2];
	for (int i = 0; i < capacity; ++i) {
		newTree[i].setValue(tree[i].getValue());
		newTree[i].setLeftSon(tree[i].getLeftSon());
		newTree[i].setRightSon(tree[i].getRightSon());
	}
	delete[] tree;
	tree = newTree;
	firstFree = capacity;
	capacity *= 2;
}
/*
Telem SortedMultiMap::getMinimum(int startingRoot)
{
	int currentNode = startingRoot, minNode = startingRoot;
	Tkey minimum;

	// caut cel mai mic element din subarborele BSB cu radacina in startingRoot
	// asta inseamna cel mai din stanga nod, adica ma duc cat de tare pot in stanga
	// o sa se afle in minNode
	while (currentNode != -1) {
		minimum = tree[currentNode].getValue();
		minNode = currentNode;
		currentNode = tree[currentNode].getLeftSon();
	}
	return minNode;

}

Telem SortedMultiMap::getMaximum(int startingRoot)
{
	return Telem();
}
*/
int SortedMultiMap::removeRecursively(int node, Telem e, bool & removed)
{
	return 0;
}

SortedMultiMap::SortedMultiMap(Relation r) : root{ -1 },
numberOfElements{ 0 },
capacity{ 16 },
firstFree{ 0 },
r{ r }
{
	tree = new BSTNode[16];
}

void SortedMultiMap::add(Tkey c, Tvalue v)
{
	if (mustBeResized()) { // daca trebuie sa redimensionam vectorul, o facem
		resize();
	}
	Telem e = std::make_pair( c, v);
	// nodul nou adaugat o sa fie pe pozitia firstFree, asa ca-l adaugam de pe acuma
	tree[firstFree].setValue(e);
	tree[firstFree].setLeftSon(-1);
	tree[firstFree].setRightSon(-1);

	// caut pozitia pe care trebuie sa adaug nodul
	// la final o sa fie "parent"
	int current = root, parent = -1;
	while (current != -1) {
		parent = current;
		if (r(e.first, tree[current].getValue().first)) // daca relatia dintre elementu pe care trebe sa-l bag si valoarea in arbore se satisface
											// atunci trebuie sa ma duc pe fiul stang
			current = tree[current].getLeftSon();
		else                                // altfel ma duc pe fiul drept
			current = tree[current].getRightSon();
	}


	if (root == -1) // caz particular - nu avem radacina => radacina este firstFree
		root = firstFree;
	else if (r(e.first, tree[parent].getValue().first)) // daca trebuie sa pun elementul pe fiul stang, il pun pe fiul stang
		tree[parent].setLeftSon(firstFree);
	else                                    // altfel, pe fiul drept
		tree[parent].setRightSon(firstFree);
	changeFirstFree(); // actualizam firstFree
	this->numberOfElements++; // crestem nr. de elemente

}

vector<Tvalue> SortedMultiMap::search(Tkey c) const
{
	int currentNode = root;
	std::vector<Tvalue> v;
	// ma duc pe fiul stang sau drept in functie de cum se stabileste relatia
	while (currentNode != -1) {
		if (tree[currentNode].getValue().first == c)
			v.push_back(tree[currentNode].getValue().second);
		if (r(c, tree[currentNode].getValue().first)) {
			currentNode = tree[currentNode].getLeftSon();
		}
		else {
			currentNode = tree[currentNode].getRightSon();
		}
	}
	return v;
}

bool SortedMultiMap::remove(Tkey c, Tvalue v)
{
	return false;
}

void SortedMultiMap::replace(Tkey k, Tvalue oldValue, Tvalue newValue)
{
}

int SortedMultiMap::size() const
{
	return this->numberOfElements;
}

bool SortedMultiMap::isEmpty() const
{
	return numberOfElements == 0;
}

/*
SMMIterator SortedMultiMap::iterator() const
{
	return SMMIterator(*this);
}
*/
vector<Tvalue> SortedMultiMap::remove_key(Tkey k)
{
	return vector<Tvalue>();
}

SortedMultiMap::~SortedMultiMap()
{
}
