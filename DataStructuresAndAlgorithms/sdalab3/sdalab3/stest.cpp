#include "stest.h"
#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <exception>
#include <vector>
#include <assert.h>
#include <iostream>

using namespace std;

bool relation1(Tkey cheie1, Tkey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll() {
	SortedMultiMap smm = SortedMultiMap(relation1);
	assert(smm.size() == 0);
	assert(smm.isEmpty());
	smm.add(1, 2);
	smm.add(1, 3);
	assert(smm.size() == 2);
	assert(!smm.isEmpty());
	vector<Tvalue> v = smm.search(1);
	assert(v.size() == 2);
	v = smm.search(3);
	assert(v.size() == 0);
	SMMIterator it = smm.iterator();
	it.first();
	while (it.valid()) {
		Telem e = it.getCurrent();
		it.next();
	}
	assert(smm.remove(1, 2) == true);
	assert(smm.remove(1, 3) == true);
	assert(smm.remove(1, 3) == false);
	assert(smm.isEmpty());
}


