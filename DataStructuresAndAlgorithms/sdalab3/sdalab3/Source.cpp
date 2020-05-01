#include "stest.h"
#include "extendedtest.h"
#include <Windows.h>
#include "SortedMultiMap.h"
#include <assert.h>

bool relation3(Tkey cheie1, Tkey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}


void test_replace()
{
	SortedMultiMap smm = SortedMultiMap(relation3);
	smm.add(1, 2);
	smm.add(1, 3);
	smm.replace(1, 2, 4);
	assert(smm.remove(1, 4) == true);

}

int main()
{
	testAll();
	testAllExtended();
	test_replace();
	system("pause");
	return 0;
}