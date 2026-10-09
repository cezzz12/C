//
// Created by Cezar on 06.04.2025.
//

#ifndef SORTEDBAGITERATOR_H
#define SORTEDBAGITERATOR_H
#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
    friend class SortedBag;

private:
    const SortedBag& bag;
    // Time Complexity: O(1) - Constant time initialization
    SortedBagIterator(const SortedBag& b);

    SortedBag::Node* currentNode;
    int currentFreqIndex;

public:
    // Time Complexity: O(1) - Returns current element
    TComp getCurrent();

    // Time Complexity: O(1) - Simple pointer check
    bool valid();

    // Time Complexity: O(1) - Constant time to move to next element
    void next();

    // Time Complexity: O(1) - Reset to first position
    void first();
};

#endif //SORTEDBAGITERATOR_H