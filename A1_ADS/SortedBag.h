//
// Created by Cezar on 25.03.2025.
//

#ifndef SORTEDBAG_H
#define SORTEDBAG_H
#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR

//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

class SortedBagIterator;

class SortedBag {
    friend class SortedBagIterator;

private:
    TComp* elements;
    int* frequencies;
    int capacity;
    int currentSize;
    int uniqueCount;
    Relation relation;

    void resize(int newCapacity);
    int findInsertIndex(TComp e) const;

public:
    //constructor
    SortedBag(Relation r);

    //adds an element to the sorted bag
    void add(TComp e);

    //removes one occurence of an element from a sorted bag
    //returns true if an eleent was removed, false otherwise (if e was not part of the sorted bag)
    bool remove(TComp e);

    //checks if an element appearch is the sorted bag
    bool search(TComp e) const;

    //returns the number of occurrences for an element in the sorted bag
    int nrOccurrences(TComp e) const;

    //returns the number of elements from the sorted bag
    int size() const;

    //returns an iterator for this sorted bag
    SortedBagIterator iterator() const;

    int removeAllOccurences(TComp elem);
    //returns and removes the occurences of a number

    //checks if the sorted bag is empty
    bool isEmpty() const;

    //destructor
    ~SortedBag();
};
#endif //SORTEDBAG_H
