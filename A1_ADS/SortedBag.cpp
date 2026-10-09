#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <exception>

SortedBag::SortedBag(Relation r) {
    // Initial capacity of 10
    capacity = 10;
    elements = new TComp[capacity];
    frequencies = new int[capacity];
    currentSize = 0;
    uniqueCount = 0;
    relation = r;
}

void SortedBag::resize(int newCapacity) {
    TComp* newElements = new TComp[newCapacity];
    int* newFrequencies = new int[newCapacity];
\
    for (int i = 0; i < uniqueCount; i++) {
        newElements[i] = elements[i];
        newFrequencies[i] = frequencies[i];
    }

    //delete old arrays
    delete[] elements;
    delete[] frequencies;

    //update to new arrays
    elements = newElements;
    frequencies = newFrequencies;
    capacity = newCapacity;
}

int SortedBag::findInsertIndex(TComp e) const {
    if (uniqueCount == 0) return 0;

    //linear search to find correct insertion point
    //liniar Complexity
    for (int i = 0; i < uniqueCount; i++) {
        if (elements[i] == e) return i;
        if (!relation(elements[i], e)) return i;
    }

    return uniqueCount;
}

void SortedBag::add(TComp e) {
    if (uniqueCount == capacity) {
        resize(capacity * 2);
    }

    int index = findInsertIndex(e);

    //if element exists, increment frequency
    if (index < uniqueCount && elements[index] == e) {
        frequencies[index]++;
    } else {
        for (int i = uniqueCount; i > index; i--)//liniar complexity
            {
            elements[i] = elements[i-1];
            frequencies[i] = frequencies[i-1];
        }

        //insert
        elements[index] = e;
        frequencies[index] = 1;
        uniqueCount++;
    }
    currentSize++;
}

bool SortedBag::remove(TComp e) {
    int index = findInsertIndex(e);

    //check if exists
    if (index < uniqueCount && elements[index] == e) {
        //decrement frequency
        frequencies[index]--;
        currentSize--;

        if (frequencies[index] == 0) {
            for (int i = index; i < uniqueCount - 1; i++) { //liniar complexity
                elements[i] = elements[i+1];
                frequencies[i] = frequencies[i+1];
            }
            uniqueCount--;
        }
        return true;
    }
    return false;
}

bool SortedBag::search(TComp elem) const {
    for (int i = 0; i < uniqueCount; i++) {
        if (elements[i] == elem) return true;
    }
    return false;
}

int SortedBag::nrOccurrences(TComp elem) const {
    for (int i = 0; i < uniqueCount; i++) {
        if (elements[i] == elem) {
            return frequencies[i];
        }
    }
    return 0;
}
int SortedBag::removeAllOccurences(TComp elem){
    int index = findInsertIndex(elem);//find elem
    if (index >= uniqueCount || elements[index] != elem) {
        return 0;
    }
    int removedCount = frequencies[index];//storing how many of elem we remove
    //shifting
    for (int i = index; i < uniqueCount - 1; i++) {
        elements[i] = elements[i+1];
        frequencies[i] = frequencies[i+1];
    }
    uniqueCount--;
    currentSize -= removedCount;

    return removedCount;
}
int SortedBag::size() const {
    return currentSize;
}

bool SortedBag::isEmpty() const {
    return currentSize == 0;
}

SortedBagIterator SortedBag::iterator() const {
    return SortedBagIterator(*this);
}

SortedBag::~SortedBag() {
    delete[] elements;
    delete[] frequencies;
}