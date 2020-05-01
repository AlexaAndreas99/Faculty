#include "Util.h"



Util::Util()
{
}

void Util::sort(vector<Dog>& vect, Comparator<Dog>* cmp)
{
	//qsort(&vect, vect.size(), sizeof(Dog), cmp->compare);
	for (int i = 0; i < vect.size() - 1; i++)
		for (int j = 0; j < vect.size(); j++)
			if (!cmp->compare(vect[i], vect[j]))
			{
				auto aux = vect[i];
				vect[i] = vect[j];
				vect[j] = aux;
			}
}


Util::~Util()
{
}
