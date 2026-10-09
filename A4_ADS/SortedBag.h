#pragma once
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#include <utility>
class SortedBagIterator;

// Node structure for BST, stores element and its frequency
struct Node {
    std::pair<TComp, int> data;  // pair of (element, frequency)
    Node* left;                  // pointer to left child
    Node* right;                 // pointer to right child
    Node(TComp elem) : data(std::make_pair(elem, 1)), left(nullptr), right(nullptr) {}
};


class SortedBag {
    friend class SortedBagIterator;
private:
    Node* root;                  // root of the BST
    Relation relation;           // comparison function for maintaining order
    int totalSize;              // total number of elements (including duplicates)
    void destroyTree(Node* node);//  destructor


public:
    // Creates an empty bag with given relation
    SortedBag(Relation r);
    void intersection(const SortedBag&b);
    // Destructor - deallocates all memory
    ~SortedBag();

    // Adds an element to the bag
    void add(TComp e);

    // Removes one occurrence of an element
    bool remove(TComp e);

    // Checks if an element appears in the bag
    bool search(TComp e) const;

    // Returns the frequency of an element
    int nrOccurrences(TComp e) const;

    // Returns total number of elements
    int size() const;

    // Checks if the bag is empty
    bool isEmpty() const;

    // Returns an iterator for the bag
    SortedBagIterator iterator() const;
};