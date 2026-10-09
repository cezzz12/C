#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"

using namespace std;

int main() {
    testAll();
    testAllExtended();
    testIntersection();
    cout << "Tests over" << endl;

}
