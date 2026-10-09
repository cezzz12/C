//
// Created by Cezar on 06.04.2025.
//

#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
    first();
}

// AC=BC=WC O(1)
TComp SortedBagIterator::getCurrent() {
    if (!valid()) {
        throw std::exception();
    }
    return bag.nodes[currentPosition].element;
}

// AC=BC=WC= O(1)
bool SortedBagIterator::valid() {
    return currentPosition != NULL_POS && currentFreqIndex < bag.nodes[currentPosition].frequency;
}

// AC=WC=BC= O(1)
void SortedBagIterator::next() {
    if (!valid()) {
        throw std::exception();
    }

    currentFreqIndex++;

    if (currentFreqIndex >= bag.nodes[currentPosition].frequency) {
        currentPosition = bag.nodes[currentPosition].next;
        currentFreqIndex = 0;
    }
}

// AC=BC=WC= O(1)
void SortedBagIterator::first() {
    currentPosition = bag.head;
    currentFreqIndex = 0;
}