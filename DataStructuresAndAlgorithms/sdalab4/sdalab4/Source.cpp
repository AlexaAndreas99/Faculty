#include "shorttest.h"
#include "extendedtest.h"
#include "SortedMultiMap.h"
#include <Windows.h>
#include <iostream>
#include <assert.h>
bool relation3(Tkey cheie1, Tkey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void test()
{
	SortedMultiMap smm = SortedMultiMap(relation3);
	smm.add(1, 2);
	smm.add(1, 3);
	vector<Tvalue> v = smm.search(1);
	assert(v[0] == 2);
	smm.replace(1, 2, 3);
	 v = smm.search(1);
	 assert(v[0] == 3);
}
int main()
{
	testAll();
	testAllExtended();
	test();
	system("pause");
	return 0;
}