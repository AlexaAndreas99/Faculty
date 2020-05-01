#pragma once
#include <vector>
#include <utility>
using namespace std;
typedef int Tkey;
typedef int Tvalue;
typedef std::pair<Tkey, Tvalue> Telem;
class SMMIterator;
typedef bool(*Relation)(Tkey, Tkey);

struct value_node 
{
	int next = -1;
	Tvalue info;
};
struct key_node 
{
	value_node *slla;
	int head = -1, first_empty = 0, cap = 5;
	int next;
	Tkey key;
};
class SortedMultiMap
{
private:
	int capacity = 5;
	int head;
	int first_empty;
	Relation r;
	key_node* nodes;
	int size_smm = 0;
	int key_values = 0;
	
	//theta(n)
	int instance(Tkey searched) const;
	//o(n)
	int find_pos(Tkey searched);
	//theta(n)
	void new_node(Tkey c, Tvalue v, int pos);
	//theta(n)
	void resize_key_node(int pos);
	//theta(n)
	void resize();
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
	SMMIterator iterator() const;
	//remove a key togheter with all its values
	//returns a vector with the values of the keys
	vector<Tvalue> remove_key(Tkey k);
	~SortedMultiMap();
};

