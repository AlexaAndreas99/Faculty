#pragma once
#include <vector>
#include "Dog.h"
#include "Comparator.h"
using namespace std;
//template <typename T>
//typedef int Telem;
typedef vector<Dog> vect;
typedef Comparator<Dog> comp;
class Util
{
public:
	Util();
	void sort(vector<Dog>& vect, Comparator<Dog>*cmp);
	~Util();
};

