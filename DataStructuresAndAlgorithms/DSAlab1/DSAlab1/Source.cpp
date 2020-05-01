#include "SortedBag.h"
#include <Windows.h>
#include <iostream>
#include <assert.h>
#include "shorttest.h"
#include "extendedtest.h"

bool relation4(Tcomp e1, Tcomp e2) {
	return e1 <= e2;
}
void test_freq()
{
	SortedBag sb(relation4);
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(10);
	sb.add(10);
	sb.add(8);
	sb.add(8);
	sb.add(8);
	std::cout<<sb.elementsWithMinimumFrequency();
}
int main()
{
	test_freq();
	testAll();
	testAllExtended();
	
	system("pause");
	return 0;


}