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
    SortedBagIterator(const SortedBag& b);

    int currentPosition;


    int currentFreqIndex;

public:
    TComp getCurrent();
    bool valid();
    void next();
    void first();
};

#endif //SORTEDBAGITERATOR_H