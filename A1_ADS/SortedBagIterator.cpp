#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
    first();
}

TComp SortedBagIterator::getCurrent() {
    if(!valid()) {
      throw std::exception();
    }
    return bag.elements[currentIndex];
}

bool SortedBagIterator::valid() {
    return currentIndex < bag.uniqueCount && currentFreqIndex < bag.frequencies[currentIndex];
}

void SortedBagIterator::next() {
    if (!valid()) {
        throw std::exception();
    }
    currentFreqIndex++;

    if (currentFreqIndex >= bag.frequencies[currentIndex]) {
        currentIndex++;
        currentFreqIndex = 0;
    }
}

void SortedBagIterator::first() {
    currentIndex = 0;
    currentFreqIndex = 0;
}

