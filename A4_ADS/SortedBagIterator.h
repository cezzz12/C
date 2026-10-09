#pragma once
#include "SortedBag.h"
#include <stack>


class SortedBagIterator {
private:
    const SortedBag& bag;            // reference to the bag
    std::stack<Node*> stack;         // stack for iterative traversal
    Node* currentNode;               // current node being processed
    int currentFrequency;            // tracks current element's frequency count

    //  push all left nodes starting from given node
    void pushAllLeft(Node* node);

public:
    SortedBagIterator(const SortedBag& b);
    void first();
    void next();
    TElem getCurrent();
    bool valid();
};