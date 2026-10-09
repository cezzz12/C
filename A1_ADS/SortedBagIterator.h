//
// Created by Cezar on 25.03.2025.
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
    SortedBagIterator(const SortedBag& b);
    int currentIndex;
    int currentFreqIndex;
public:
    TComp getCurrent(); //returns to current
    bool valid();   //checks if iterator valid
    void next();    //moves to next
    void first(); //resets to first
};


#endif //SORTEDBAGITERATOR_H
