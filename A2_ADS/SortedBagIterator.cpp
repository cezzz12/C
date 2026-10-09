//
// Created by Cezar on 06.04.2025.
//

#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

// Time Complexity: O(1) - Constant time initialization
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
    first();
}

// Time Complexity: O(1) - Returns current element
TComp SortedBagIterator::getCurrent() {
    if (!valid()) {
        throw std::exception();
    }
    return currentNode->element;
}

// Time Complexity: O(1) - Simple pointer check
bool SortedBagIterator::valid() {
    return currentNode != nullptr && currentFreqIndex < currentNode->frequency;
}

// Time Complexity: O(1) - Constant time to move to next element
void SortedBagIterator::next() {
    if (!valid()) {
        throw std::exception();
    }

    currentFreqIndex++;

    if (currentFreqIndex >= currentNode->frequency) {
        currentNode = currentNode->next;
        currentFreqIndex = 0;
    }
}

// Time Complexity: O(1) - Reset to first position
void SortedBagIterator::first() {
    currentNode = bag.head;
    currentFreqIndex = 0;
}