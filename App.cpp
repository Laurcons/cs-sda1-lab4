#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <crtdbg.h>

using namespace std;

int main() {
	testAll();
	testAllExtended();

	if (_CrtDumpMemoryLeaks())
		cout << "MEMORY LEAKS DETECTED!!!!!!!!!!!!!!!" << endl;
	else cout << "Memory correctly deallocated." << endl;
	
	cout << "Test over" << endl;
	system("pause");
}
