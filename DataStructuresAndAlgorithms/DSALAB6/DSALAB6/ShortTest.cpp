#include "ShortTest.h"
#include <assert.h>
#include "Set.h"
#include "SetIterator.h"
#include <math.h>
#include <iostream>

int hash7(TKey k, int cap)
{
	return abs(k % cap);
}

void testDiff()
{

	Set s{ hash7 };
	assert(s.isEmpty() == true);
	assert(s.size() == 0);
	assert(s.add(5) == true);
	assert(s.add(1) == true);
	assert(s.add(10) == true);
	assert(s.add(7) == true);
	assert(s.size() == 4);

	Set m{ hash7 };
	assert(m.isEmpty() == true);
	assert(m.size() == 0);
	assert(m.add(4) == true);
	assert(m.add(1) == true);
	assert(m.add(10) == true);
	assert(m.add(7) == true);

	s.difference(m);
	//std::cout<<s.difference(m)<<std::endl;
	//std::cout<<s.size();
	assert(s.size() == 1);
}

void testAll() { 
	testDiff();
	Set s{ hash7 };
	assert(s.isEmpty() == true);
	assert(s.size() == 0); 
	assert(s.add(5)==true);
	assert(s.add(1)==true);
	assert(s.add(10)==true);
	assert(s.add(7)==true);
	assert(s.add(1)==false);
	assert(s.add(1)==false);
	assert(s.add(-3)==true);
	assert(s.size() == 5);
	assert(s.search(10) == true);
	assert(s.search(16) == false);
	assert(s.remove(1) == true);
	assert(s.remove(6) == false);
	//std::cout << s.size()<<std::endl;
	assert(s.size() == 4);


	SetIterator it = s.iterator();
	it.first();
	int sum = 0;
	while (it.valid()) {
		TKey e = it.getCurrent();
		sum += e;
		//std::cout << e << std::endl;
		it.next();
	}
	assert(sum == 19);

}

