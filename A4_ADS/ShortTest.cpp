#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <assert.h>
#include <iostream>
bool relation1(TComp e1, TComp e2) {
    return e1 <= e2;
}

void testAll() {
    SortedBag sb(relation1);
    sb.add(5);
    sb.add(6);
    sb.add(0);
    sb.add(5);
    sb.add(10);
    sb.add(8);

    assert(sb.size() == 6);
    assert(sb.nrOccurrences(5) == 2);

    assert(sb.remove(5) == true);
    assert(sb.size() == 5);

    assert(sb.search(6) == true);
    assert(sb.isEmpty() == false);

    SortedBagIterator it = sb.iterator();
    assert(it.valid() == true);
    while (it.valid()) {
        it.getCurrent();
        it.next();
    }
    assert(it.valid() == false);
    it.first();
    assert(it.valid() == true);

}
void testIntersection() {
    //Basic intersection with common elements
    SortedBag sb1(relation1);
    sb1.add(1);
    sb1.add(3);
    sb1.add(5);
    sb1.add(5);
    sb1.add(7);

    SortedBag sb2(relation1);
    sb2.add(3);
    sb2.add(5);
    sb2.add(5);
    sb2.add(5);
    sb2.add(9);

    sb1.intersection(sb2);

    assert(sb1.size() == 3);
    assert(sb1.nrOccurrences(1) == 0);
    assert(sb1.nrOccurrences(3) == 1);
    assert(sb1.nrOccurrences(5) == 2);
    assert(sb1.nrOccurrences(7) == 0);
    assert(sb1.nrOccurrences(9) == 0);

    //Empty intersection
    SortedBag sb3(relation1);
    sb3.add(1);
    sb3.add(2);

    SortedBag sb4(relation1);
    sb4.add(10);
    sb4.add(20);

    sb3.intersection(sb4);
    assert(sb3.size() == 0);
    assert(sb3.isEmpty() == true);
    std::cout<<"Intersection test passed!"<<std::endl;

}
