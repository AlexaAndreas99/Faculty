#pragma once
#include <utility>
typedef int Tkey;
typedef int Tvalue;
typedef std::pair<Tkey, Tvalue> Telem;
class BSTNode
{
private:
	Telem value;
	int left;
	int right;

public:
	BSTNode();
	BSTNode(Telem v, int l ,int r);
	Telem getValue() const;
	void setValue(Telem e);
	int getLeftSon() const;
	void setLeftSon(int leftSon);
	int getRightSon() const;
	void setRightSon(int rightSon);
	bool isNull(); // returneaza true sau false daca e nul
	bool isLeaf(); // returneaza daca e frunza sau nu (adica nu are deloc fii)

	~BSTNode();
};

