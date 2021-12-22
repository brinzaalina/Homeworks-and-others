#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <crtdbg.h>

using namespace std;

int main() {
	testAll();
	testExtra();
	testAllExtended();
    _CrtDumpMemoryLeaks();
	cout << "Test over" << endl;
	system("pause");
}
